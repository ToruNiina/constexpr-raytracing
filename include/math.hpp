#ifndef CONSTEXPR_RAYTRACING_MATH_HPP
#define CONSTEXPR_RAYTRACING_MATH_HPP
#include <limits>
#include <numbers>

#include <cmath>

namespace conray
{
namespace math
{

constexpr inline std::size_t sqrt_N = 256;
constexpr inline double sqrt_dx = (1.0 - 0.5) / sqrt_N;
constexpr inline double sqrt_a[sqrt_N] = {
#include "parameters/sqrt_a.dat"
};
constexpr inline double sqrt_b[sqrt_N] = {
#include "parameters/sqrt_b.dat"
};
constexpr inline double sqrt_c[sqrt_N] = {
#include "parameters/sqrt_c.dat"
};

constexpr double sqrt_interp(const double x)
{
    const std::size_t i = (x - 0.5) / sqrt_dx;
    const auto a = sqrt_a[i];
    const auto b = sqrt_b[i];
    const auto c = sqrt_c[i];
    return (a * x + b) * x + c;
}

// std::sqrt is marked constexpr in C++26
constexpr double sqrt(const double x)
{
    if(x == 0.0 || x == -0.0)
    {
        return 0.0;
    }
    if(std::isnan(x) || x < -0.0)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if(std::isinf(x))
    {
        return std::numeric_limits<double>::infinity();
    }

    int ex=0;
    const double norm = std::frexp(x, &ex);

    const int zex = ex / 2;
    if(ex >= 0)
    {
        if(ex % 2 == 1)
        {
            const double z = sqrt_interp(norm) * std::numbers::sqrt2;
            return std::ldexp(z, zex);
        }
        else
        {
            const double z = sqrt_interp(norm);
            return std::ldexp(z, zex);
        }
    }
    else
    {
        if(ex % 2 == -1)
        {
            const double z = sqrt_interp(norm) / std::numbers::sqrt2;
            return std::ldexp(z, zex);
        }
        else
        {
            const double z = sqrt_interp(norm);
            return std::ldexp(z, zex);
        }
    }
}

constexpr inline std::size_t rsqrt_N = 256;
constexpr inline double rsqrt_dx = (1.0 - 0.5) / rsqrt_N;
constexpr inline double rsqrt_a[rsqrt_N] = {
#include "parameters/rsqrt_a.dat"
};
constexpr inline double rsqrt_b[rsqrt_N] = {
#include "parameters/rsqrt_b.dat"
};
constexpr inline double rsqrt_c[rsqrt_N] = {
#include "parameters/rsqrt_c.dat"
};

constexpr double rsqrt_interp(const double x)
{
    const std::size_t i = (x - 0.5) / rsqrt_dx;
    const auto a = rsqrt_a[i];
    const auto b = rsqrt_b[i];
    const auto c = rsqrt_c[i];
    return (a * x + b) * x + c;
}

// std::rsqrt is marked constexpr in C++26
constexpr double rsqrt(const double x)
{
    if(x == 0.0 || x == -0.0)
    {
        return 0.0;
    }
    if(std::isnan(x) || x < -0.0)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    if(std::isinf(x))
    {
        return std::numeric_limits<double>::infinity();
    }

    int ex=0;
    const double norm = std::frexp(x, &ex);

    const int zex = -ex / 2;
    if(ex >= 0)
    {
        if(ex % 2 == 1)
        {
            const double z = rsqrt_interp(norm) / std::numbers::sqrt2;
            return std::ldexp(z, zex);
        }
        else
        {
            const double z = rsqrt_interp(norm);
            return std::ldexp(z, zex);
        }
    }
    else
    {
        if(ex % 2 == -1)
        {
            const double z = rsqrt_interp(norm) * std::numbers::sqrt2;
            return std::ldexp(z, zex);
        }
        else
        {
            const double z = rsqrt_interp(norm);
            return std::ldexp(z, zex);
        }
    }
}

} // math
} // conray
#endif// CONSTEXPR_RAYTRACING_MATH_HPP
