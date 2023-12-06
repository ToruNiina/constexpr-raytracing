#ifndef CONSTEXPR_RAYTRACING_TOOLS_INTERPOLATION
#define CONSTEXPR_RAYTRACING_TOOLS_INTERPOLATION

#include <cstddef>

namespace math
{
template<typename T, std::size_t N>
struct polynomial;

template<typename T>
struct polynomial<T, 2>
{
    using value_type = T;

    template<typename F, typename dF>
    constexpr polynomial(T x0, T x1, F f, dF df)
    {
        const auto dfx0 = df(x0);
        const auto dfx1 = df(x1);

        // df(x0) = 2ax0 + b
        // df(x1) = 2ax1 + b
        // df(x1) - df(x0) = 2a(x1 - x0)

        this->a = (dfx1 - dfx0) / (2.0 * (x1 - x0));
        this->b = dfx0 - (2 * a * x0);

        const auto fx0 = f(x0);
        // f(x0) = ax0^2 + bx0 + c
        this->c = fx0 - a * x0 * x0 - b * x0;
    }

    constexpr value_type operator()(const value_type x) const noexcept
    {
        return (a * x + b) * x + c;
    }

  public:

    value_type a;
    value_type b;
    value_type c;
};

template<typename T>
struct polynomial<T, 3>
{
    using value_type = T;

    template<typename F, typename dF, typename ddF>
    constexpr polynomial(T x0, T x1, F f, dF df, ddF ddf)
    {
        const auto ddfx0 = ddf(x0);
        const auto ddfx1 = ddf(x1);

        // ddf(x0) = 6ax0 + 2b
        // ddf(x1) = 6ax1 + 2b
        //
        // ddf(x1) - ddf(x0) = 6a(x1 - x0)

        this->a = (ddfx1 - ddfx0) / (6.0 * (x1 - x0));
        this->b = (ddfx0 - 6.0 * a * x0) * 0.5;

        const auto dfx0 = df(x0);
        // df(x0) = 3ax0^2 + 2bx0 + c
        this->c = dfx0 - 3 * a * x0 * x0 - 2 * b * x0;

        const auto fx0 = f(x0);
        // f(x0) = ax0^3 + bx0^2 + cx0 + d
        this->d = fx0 - a * x0 * x0 * x0 - b * x0 * x0 - c * x0;
    }

    constexpr value_type operator()(const value_type x) const noexcept
    {
        return ((a * x + b) * x + c) * x + d;
    }

  public:

    value_type a;
    value_type b;
    value_type c;
    value_type d;
};

} // math
#endif // CONSTEXPR_RAYTRACING_TOOLS_INTERPOLATION
