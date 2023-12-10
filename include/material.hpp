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

} // conray
#endif// CONSTEXPR_RAYTRACING_MATERIAL_HPP
