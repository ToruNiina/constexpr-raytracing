#ifndef CONSTEXPR_RAYTRACING_RANDOM_HPP
#define CONSTEXPR_RAYTRACING_RANDOM_HPP

#include <cstdint>

namespace conray
{

struct xorshift64
{
    std::uint64_t state;
};

constexpr xorshift64 next(const xorshift64& curr) noexcept
{
    std::uint64_t x = curr.state;
    x ^= x << 13;
    x ^= x >>  7;
    x ^= x << 17;
    return xorshift64{x};
}

constexpr std::pair<double, xorshift64> uniform_12(const xorshift64 rng) noexcept
{
    static_assert(std::numeric_limits<double>::is_iec559, "assuming IEEE 754");

    const auto nrng = next(rng);

    const std::uint64_t mantissa_mask   = (1ull << 52) - 1;
    const std::uint64_t random_mantissa = nrng.state & mantissa_mask;
    const std::uint64_t exponent_bias   = 1023 << 52;
    const std::uint64_t float64         = exponent_bias + random_mantissa

    return std::make_pair(std::bit_cast<double>(float64), nrng);
}
constexpr std::pair<double, xorshift64> uniform_01(const xorshift64 rng) noexcept
{
    const auto [d, r] = uniform_12(rng);
    return std::make_pair(d - 1.0, r);
}

constexpr double uniform_on_sphere_surface(xorshift64 rng0) noexcept
{
    while(true)
    {
        const auto [x, rng1] = uniform_01(rng0);
        const auto [y, rng2] = uniform_01(rng1);
        const auto [z, rng3] = uniform_01(rng2);

        const math::vector v{x * 2.0 - 1.0, y * 2.0 - 1.0, z * 2.0 - 1.0};
        const auto l = length(v);
        if(l <= 1.0)
        {
            return make_pair(v / l, rng3);
        }
        rng0 = rng3;
    }
}

} // conray
#endif//CONSTEXPR_RAYTRACING_RANDOM_HPP
