#ifndef CONSTEXPR_RAYTRACING_WORLD_HPP
#define CONSTEXPR_RAYTRACING_WORLD_HPP

#include "collision.hpp"
#include "sphere.hpp"

#include <array>
#include <optional>
#include <variant>

namespace conray
{

template<std::size_t N>
struct world
{
    std::array<std::variant<sphere>, N> objects;
};

template<typename ... Ts>
constexpr world<sizeof...(Ts)> make_world(Ts ... objs)
{
    return world<sizeof...(Ts)>{
        .objects{std::move(objs)...}
    };
}

template<std::size_t N>
constexpr std::optional<collision_info>
collides(const ray& r, const world<N>& w, const double t_min, const double t_max) noexcept
{
    for(const auto& object : w.objects)
    {
        if(const auto hit = std::visit([&r, t_min, t_max](const auto& obj) {
                return collides(r, obj, t_min, t_max);
            }, object))
        {
            return hit;
        }
    }
    return std::nullopt;
}

} // world
#endif//CONSTEXPR_RAYTRACING_WORLD_HPP
