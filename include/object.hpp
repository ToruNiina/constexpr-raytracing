#ifndef CONSTEXPR_RAYTRACING_OBJECT_HPP
#define CONSTEXPR_RAYTRACING_OBJECT_HPP

#include "sphere.hpp"
#include "material.hpp"
#include "color.hpp"

#include <array>
#include <optional>
#include <variant>

namespace conray
{

struct object
{
    color attenuation;
    std::variant<diffusive, metallic, dielectric> material;
    std::variant<sphere> shape;
};

} // conray
#endif//CONSTEXPR_RAYTRACING_OBJECT_HPP
