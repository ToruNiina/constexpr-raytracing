#ifndef CONSTEXPR_RAYTRACING_OBJECT_HPP
#define CONSTEXPR_RAYTRACING_OBJECT_HPP

#include "sphere.hpp"
#include "material.hpp"

#include <array>
#include <optional>
#include <variant>

namespace conray
{

struct object
{
    std::variant<diffusive> material;
    std::variant<sphere>    shape;
};

} // conray
#endif//CONSTEXPR_RAYTRACING_OBJECT_HPP
