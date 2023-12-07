#ifndef CONSTEXPR_RAYTRACING_VECTOR_HPP
#define CONSTEXPR_RAYTRACING_VECTOR_HPP

#include "math.hpp"

namespace conray
{
namespace math
{

struct vector
{
  public:

    constexpr vector& operator+=(const vector& other) noexcept
    {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }
    constexpr vector& operator-=(const vector& other) noexcept
    {
        this->x -= other.x;
        this->y -= other.y;
        this->z -= other.z;
        return *this;
    }
    constexpr vector& operator*=(const double other) noexcept
    {
        this->x *= other;
        this->y *= other;
        this->z *= other;
        return *this;
    }
    constexpr vector& operator/=(const double other) noexcept
    {
        this->x /= other;
        this->y /= other;
        this->z /= other;
        return *this;
    }

  public:

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

constexpr inline vector operator-(const vector& v) noexcept
{
    return vector{-v.x, -v.y, -v.z};
}
constexpr inline vector operator+(const vector& lhs, const vector& rhs) noexcept
{
    return vector{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}
constexpr inline vector operator-(const vector& lhs, const vector& rhs) noexcept
{
    return vector{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}
constexpr inline vector operator*(const double lhs, const vector& rhs) noexcept
{
    return vector{lhs * rhs.x, lhs * rhs.y, lhs * rhs.z};
}
constexpr inline vector operator*(const vector& lhs, const double rhs) noexcept
{
    return vector{lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}
constexpr inline vector operator/(const vector& lhs, const double rhs) noexcept
{
    return vector{lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

constexpr inline double length_sq(const vector& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}
constexpr inline double length(const vector& v)
{
    return sqrt(length_sq(v));
}
constexpr inline double rlength(const vector& v)
{
    return rsqrt(length_sq(v));
}
constexpr inline vector normalize(const vector& v)
{
    return rsqrt(length_sq(v)) * v;
}

constexpr inline double dot_product(const vector& lhs, const vector& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
constexpr inline vector cross_product(const vector& lhs, const vector& rhs)
{
    return vector {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}
constexpr inline vector hadamard_product(const vector& lhs, const vector& rhs)
{
    return vector {
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z
    };
}

} // math
} // conray
#endif// CONSTEXPR_RAYTRACING_VECTOR_HPP
