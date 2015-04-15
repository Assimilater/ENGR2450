#include "a6p1.hpp"
#include <iomanip>
#include <iostream>
#include <functional>
#include <map>

#include "../shared/decimal.hpp"

typedef std::function<double(const decimal&, const double&)> ODE;
typedef std::map<decimal, double> Table;
typedef std::pair<decimal, double> Point;

Table RK4(ODE f, Point init, decimal t_final, double h) {
    double k1, k2, k3, k4,
        s = init.second;
    decimal t = init.first;

    Table data{init};
    do {
        k1 = f(t, s);
        k2 = f(t + h / 2, s + k1 * h / 2);
        k3 = f(t + h / 2, s + k2 * h / 2);
        k4 = f(t + h, s + k3 * h);

        s += h * (k1 + 2 * (k2 + k3) + k4) / 6;
        t += h;

        data.insert(std::make_pair(t, s));
    } while (t < t_final);

    return data;
}

void assign6::Prob1() {
    Table exact{
        {1950, 2555},
        {1960, 3040},
        {1970, 3708},
        {1980, 4454},
        {1990, 5276},
        {2000, 6079},
    };
    Table actual{
        {1950, 2555},
        {1960, 3040},
        {1970, 3708},
        {1980, 4454},
        {1990, 5276},
        {2000, 6079},
    };

    const double kgm = 0.026;
    const double pmax = 12000; // p measured in millions
    ODE dpdt = [&kgm, &pmax](const decimal& t, const double& p) {
        return kgm * (1 - p / pmax) * p;
    };

    Table results = RK4(dpdt, std::make_pair(1950, 2555), 2000, 0.1);

    std::cout << "Problem 1: " << std::left << std::endl
        << std::setw(10) << "t"
        << std::setw(10) << "p"
        << std::setw(10) << "p_exact"
        << std::setw(10) << "p_actual"
        << std::endl
        << "----------------------------------------" << std::endl;
    for (decimal year = 1950; year <= 2000; year += 10) {
        std::cout
            << std::setw(10) << (double)year
            << std::setw(10) << results[year]
            << std::setw(10) << exact[year]
            << std::setw(10) << actual[year]
            << std::endl;
    }
    std::cout << std::endl;
}
