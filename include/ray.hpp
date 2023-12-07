#ifndef CONSTEXPR_RAYTRACING_RAY_HPP
#define CONSTEXPR_RAYTRACING_RAY_HPP

#include "vector.hpp"

namespace conray
{

struct ray
{
    math::vector origin;
    math::vector direction;
};

} // conray
#endif// CONSTEXPR_RAYTRACING_RAY_HPP
