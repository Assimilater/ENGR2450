#include "a6p4.hpp"
#include <iomanip>
#include <iostream>
#include <functional>
#include <type_traits>
#include <map>

#include "../shared/decimal.hpp"

struct s3eqs {
    double x, y, z;

    s3eqs() : x(0), y(0), z(0) {}
    s3eqs(double sx, double sy, double sz) : x(sx), y(sy), z(sz) {}
    s3eqs(const s3eqs& s) { x = s.x; y = s.y; z = s.z; }
    template <typename N, typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
    s3eqs(const N& n) { x = n; y = n; z = n; }

    s3eqs& operator+= (const s3eqs& s) { x += s.x; y += s.y; z += s.z; return *this; }
    s3eqs& operator-= (const s3eqs& s) { x -= s.x; y -= s.y; z -= s.z; return *this; }
    s3eqs& operator*= (const s3eqs& s) { x *= s.x; y *= s.y; z *= s.z; return *this; }
    s3eqs& operator/= (const s3eqs& s) { x /= s.x; y /= s.y; z /= s.z; return *this; }
    friend s3eqs operator+ (const s3eqs& l, const s3eqs& r) { return s3eqs(l) += r; }
    friend s3eqs operator- (const s3eqs& l, const s3eqs& r) { return s3eqs(l) -= r; }
    friend s3eqs operator* (const s3eqs& l, const s3eqs& r) { return s3eqs(l) *= r; }
    friend s3eqs operator/ (const s3eqs& l, const s3eqs& r) { return s3eqs(l) /= r; }
};

typedef std::function<s3eqs(const decimal&, const s3eqs&)> ODE;
typedef std::map<decimal, s3eqs> Table;
typedef std::pair<decimal, s3eqs> Point;

Table RK4(ODE f, Point init, decimal t_final, double h) {
    s3eqs k1, k2, k3, k4,
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

void assign6::Prob4() {
    const double sigma = 10, b = 2.66666667, r = 28;
    ODE dsdt = [&sigma, &b, &r](const decimal& t, const s3eqs& s) {
        s3eqs ds;
        ds.x = -sigma * s.x + sigma * s.y;
        ds.y = r * s.x - s.y - s.x * s.z;
        ds.z = -b * s.z + s.x * s.y;
        return ds;
    };

    Table results = RK4(dsdt, std::make_pair(0, 5), 20, 0.1);

    std::cout << "Problem 4: " << std::left << std::endl
        << std::setw(7) << "t"
        << std::setw(15) << "x(t)"
        << std::setw(15) << "y(t)"
        << std::setw(15) << "z(t)"
        << std::endl
        << "----------------------------------------------" << std::endl;
    for (decimal t = 0; t <= 20; t += 2) {
        std::cout
            << std::setw(7) << (double)t
            << std::setw(15) << results[t].x
            << std::setw(15) << results[t].y
            << std::setw(15) << results[t].z
            << std::endl;
    }
    std::cout << std::endl;
}
