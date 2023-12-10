#ifndef CONSTEXPR_RAYTRACING_MATERIAL_HPP
#define CONSTEXPR_RAYTRACING_MATERIAL_HPP

#include "vector.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "collision.hpp"

namespace conray
{

struct diffusive{};

template<typename RNG>
constexpr std::pair<ray, RNG>
scatter(const ray&, const collision_info& info, const diffusive&, const RNG rng)
{
    const auto [dir0, nrng] = uniform_on_sphere_surface(rng);
    const auto dir = dir0 + info.normal;

    return std::make_pair(ray{info.position, math::normalize(dir)}, nrng);
};

struct metallic
{
    double fuzziness;
};

constexpr math::vector reflect(const math::vector v, const math::vector n)
{
    return v - 2.0 * math::dot_product(v, n) * n;
}

template<typename RNG>
constexpr std::pair<ray, RNG>
scatter(const ray& r_in, const collision_info& info, const metallic& mat, const RNG rng)
{
    const auto [dir0, nrng] = uniform_on_sphere_surface(rng);
    const auto dir = reflect(r_in.direction, info.normal) + mat.fuzziness * dir0;
    return std::make_pair(ray{info.position, dir}, nrng);
}

struct dielectric
{
    double refidx;
};

constexpr double schlick(const double refidx, const double cosine)
{
    const double r = (1.0 - refidx) / (1.0 + refidx);
    const double r2 = r * r;

    const auto cos  = 1.0 - cosine;
    const auto cos2 = cos * cos;
    const auto cos4 = cos2 * cos2;
    return r2 + (1.0 - r2) * cos4 * cos;
}

constexpr std::optional<math::vector>
refract(const math::vector v, const math::vector n, const double v_dot_n, const double ni_over_nt)
{
    const double d = 1.0 - ni_over_nt * ni_over_nt * (1.0 - v_dot_n * v_dot_n);
    if(d < 0.0)
    {
        return std::nullopt;
    }
    return ni_over_nt * (v - n * v_dot_n) - n * sqrt(d);
}

template<typename RNG>
constexpr std::pair<ray, RNG>
scatter(const ray& r_in, const collision_info& info, const dielectric& mat, const RNG rng)
{
    const auto dir_dot_normal = math::dot_product(r_in.direction, info.normal);
    const auto [out_normal, ni_over_nt, cos] = (dir_dot_normal > 0.0) ?
        std::make_tuple(-info.normal,       mat.refidx,  dir_dot_normal) :
        std::make_tuple( info.normal, 1.0 / mat.refidx, -dir_dot_normal);

    if(const auto refracted = refract(r_in.direction, out_normal, -cos, ni_over_nt))
    {
        const auto [rnd, nrng] = uniform_01(rng);
        if(rnd < schlick(mat.refidx, cos))
        {
            const auto dir = reflect(r_in.direction, info.normal);
            return std::make_pair(ray{info.position, dir}, nrng);
        }
        return std::make_pair(ray{info.position, *refracted}, nrng);
    }
    else
    {
        const auto dir = reflect(r_in.direction, info.normal);
        return std::make_pair(ray{info.position, dir}, rng);
    }
}


} // conray
#endif// CONSTEXPR_RAYTRACING_MATERIAL_HPP
