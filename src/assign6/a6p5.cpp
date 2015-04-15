#include "a6p5.hpp"
#include <iomanip>
#include <iostream>
#include <functional>
#include <type_traits>
#include <math.h>
#include <map>

#include "../shared/decimal.hpp"

struct s2eqs {
    double y1, y2;

    s2eqs() : y1(0), y2(0) {}
    s2eqs(double sx, double sy, double sz) : y1(sx), y2(sy) {}
    s2eqs(const s2eqs& s) { y1 = s.y1; y2 = s.y2; }
    template <typename N, typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
    s2eqs(const N& n) { y1 = n; y2 = n; }

    s2eqs& operator+= (const s2eqs& s) { y1 += s.y1; y2 += s.y2; return *this; }
    s2eqs& operator-= (const s2eqs& s) { y1 -= s.y1; y2 -= s.y2; return *this; }
    s2eqs& operator*= (const s2eqs& s) { y1 *= s.y1; y2 *= s.y2; return *this; }
    s2eqs& operator/= (const s2eqs& s) { y1 /= s.y1; y2 /= s.y2; return *this; }
    friend s2eqs operator+ (const s2eqs& l, const s2eqs& r) { return s2eqs(l) += r; }
    friend s2eqs operator- (const s2eqs& l, const s2eqs& r) { return s2eqs(l) -= r; }
    friend s2eqs operator* (const s2eqs& l, const s2eqs& r) { return s2eqs(l) *= r; }
    friend s2eqs operator/ (const s2eqs& l, const s2eqs& r) { return s2eqs(l) /= r; }
};

typedef std::function<s2eqs(const decimal&, const s2eqs&)> ODE;
typedef std::map<decimal, s2eqs> Table;
typedef std::pair<decimal, s2eqs> Point;

Table RK4(ODE f, Point init, decimal t_final, double h) {
    s2eqs k1, k2, k3, k4,
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

void assign6::Prob5() {
    const double f = 60, L = 30, E = 125000000, I = 0.05;
    ODE dsdt = [&f, &L, &E, &I](const decimal& z, const s2eqs& s) {
        s2eqs ds;
        double temp = L - (double)z;
        ds.y1 = s.y2;
        ds.y2 = f * temp * temp / (2 * E * I);
        return ds;
    };

    Table results = RK4(dsdt, std::make_pair(0, 0), L, 0.5);

    std::cout << "Problem 5: " << std::left << std::endl
        << std::setw(7) << "z"
        << std::setw(10) << "y'(z)"
        << std::setw(10) << "y''(z)"
        << std::endl
        << "-------------------------" << std::endl;
    for (decimal z = 0; z <= L; z += 5) {
        std::cout
            << std::setw(7) << (double)z
            << std::setw(10) << results[z].y1
            << std::setw(10) << results[z].y2
            << std::endl;
    }
    std::cout << std::endl;
}
