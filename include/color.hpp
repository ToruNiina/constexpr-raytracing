#ifndef CONSTEXPR_RAYTRACING_COLOR_HPP
#define CONSTEXPR_RAYTRACING_COLOR_HPP

#include "math.hpp"

#include <algorithm>

namespace conray
{

struct color
{
  public:

    constexpr color& operator+=(const color& other) noexcept
    {
        this->r += other.r;
        this->g += other.g;
        this->b += other.b;
        return *this;
    }
    constexpr color& operator-=(const color& other) noexcept
    {
        this->r -= other.r;
        this->g -= other.g;
        this->b -= other.b;
        return *this;
    }
    constexpr color& operator*=(const double other) noexcept
    {
        this->r *= other;
        this->g *= other;
        this->b *= other;
        return *this;
    }
    constexpr color& operator/=(const double other) noexcept
    {
        this->r /= other;
        this->g /= other;
        this->b /= other;
        return *this;
    }

  public:

    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
};

constexpr inline color operator-(const color& v) noexcept
{
    return color{-v.r, -v.g, -v.b};
}
constexpr inline color operator+(const color& lhs, const color& rhs) noexcept
{
    return color{lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b};
}
constexpr inline color operator-(const color& lhs, const color& rhs) noexcept
{
    return color{lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b};
}
constexpr inline color operator*(const double lhs, const color& rhs) noexcept
{
    return color{lhs * rhs.r, lhs * rhs.g, lhs * rhs.b};
}
constexpr inline color operator*(const color& lhs, const double rhs) noexcept
{
    return color{lhs.r * rhs, lhs.g * rhs, lhs.b * rhs};
}
constexpr inline color operator/(const color& lhs, const double rhs) noexcept
{
    return color{lhs.r / rhs, lhs.g / rhs, lhs.b / rhs};
}

struct pixel
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
};

constexpr inline pixel to_pixel(const color& col) noexcept
{
    return pixel{
        static_cast<std::uint8_t>(255.999 * std::clamp(col.r, 0.0, 1.0)),
        static_cast<std::uint8_t>(255.999 * std::clamp(col.g, 0.0, 1.0)),
        static_cast<std::uint8_t>(255.999 * std::clamp(col.b, 0.0, 1.0))
    };
}

} // conray
#endif// CONSTEXPR_RAYTRACING_VECTOR_HPP
