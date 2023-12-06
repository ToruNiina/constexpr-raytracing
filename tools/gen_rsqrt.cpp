#include "interpolation.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

#include <cmath>

//      x^-1/2
// -1/2 x^-3/2
//  3/4 x^-5/2
double f(double x)
{
    return 1.0 / std::sqrt(x);
}
double df(double x)
{
    return -0.5 / (x * std::sqrt(x));
}
double ddf(double x)
{
    return 0.75 / (x * x * std::sqrt(x));
}

int main()
{
    constexpr std::size_t N = 256;

    const double begin = 0.5;
    const double end   = 1.0;
    const double dx = (end - begin) / N;

    std::ofstream a("rsqrt_a.dat");
    std::ofstream b("rsqrt_b.dat");
    std::ofstream c("rsqrt_c.dat");

    for(std::size_t i=0; i<N; ++i)
    {
        if(i != 0)
        {
            a << ",\n";
            b << ",\n";
            c << ",\n";
        }

        // define {a, b, c} for range [x0 + dx*i ~ x0 + dx*(i+1))
        const double x0 = begin + dx *  i;
        const double x1 = begin + dx * (i+1);

        math::polynomial<double, 2> p(x0, x1, f, df);

        a << std::setprecision(16) << p.a;
        b << std::setprecision(16) << p.b;
        c << std::setprecision(16) << p.c;
    }
    return 0;
}
