#ifndef CONSTEXPR_RAYTRACING_COLLISION_HPP
#define CONSTEXPR_RAYTRACING_COLLISION_HPP

#include "ray.hpp"
#include "sphere.hpp"
#include "vector.hpp"

#include <optional>

namespace conray
{

struct collision_info
{
    double t;
    math::vector normal;
};

constexpr std::optional<collision_info>
collides(const ray& r, const sphere& s, const double t_min, const double t_max) noexcept
{
    const auto oc = r.origin - s.center;
    // r.direction is always normalized
    const auto b  = dot_product(oc, r.direction);
    const auto c  = math::length_sq(oc) - s.radius * s.radius;
    const auto d  = b * b - c;
    if(d < 0) { return std::nullopt; }

    const auto t = -b - math::sqrt(d);
    if(t_min <= t && t <= t_max)
    {
        const auto n = oc + t * r.direction;
        return collision_info{ t, normalize(n) };
    }
    return std::nullopt;
}

} // conray
#endif// CONSTEXPR_RAYTRACING_SPHERE_HPP
