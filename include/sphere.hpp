#ifndef CONSTEXPR_RAYTRACING_SPHERE_HPP
#define CONSTEXPR_RAYTRACING_SPHERE_HPP

#include "vector.hpp"

namespace conray
{

struct sphere
{
    math::vector center;
    double       radius;
};

} // conray
#endif// CONSTEXPR_RAYTRACING_SPHERE_HPP
