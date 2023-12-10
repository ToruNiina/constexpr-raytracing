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
    math::vector position;
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

    if(const auto t = -b - math::sqrt(d); t_min <= t && t <= t_max)
    {
        const auto pos = r.origin + t * r.direction;
        const auto n   = math::normalize(pos - s.center);

        return collision_info{ t, n, pos };
    }

    if(const auto t = -b + math::sqrt(d); t_min <= t && t <= t_max)
    {
        const auto pos = r.origin + t * r.direction;
        const auto n   = math::normalize(pos - s.center);

        return collision_info{ t, n, pos };
    }
    return std::nullopt;
}

} // conray
#endif// CONSTEXPR_RAYTRACING_SPHERE_HPP
