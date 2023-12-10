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
scatter(const collision_info& info, const diffusive& mat, const RNG rng)
{
    const auto [dir0, nrng] = uniform_on_sphere_surface(rng);
    const auto dir = dir0 + info.normal;

    return std::make_pair(ray{info.position, math::normalize(dir)}, nrng);
};

} // conray
#endif// CONSTEXPR_RAYTRACING_MATERIAL_HPP
