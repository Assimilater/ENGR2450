#include "assign5.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <math.h>
#include "../shared/helpers.hpp"

#pragma region Problems 1 and 2
double Trapm(const std::vector<double> f, double h) {
    int n = f.size() - 1;
    double sum = f[0];
    for (int i = 1; i < n; ++i) {
        sum += 2 * f[i];
    }
    sum += f[n];
    return h * sum / 2;
}
double Trapm(const std::vector<double> x, const std::vector<double> y) {
    int n = x.size();
    double sum = 0;
    for (int i = 1; i < n; ++i) {
        sum += (x[i] - x[i - 1]) * (y[i] + y[i - 1]) / 2;
    }
    return sum;
}
double Trapm(std::function<double(double)> f, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = f(a);
    for (int i = 1; i < n; ++i) {
        sum += 2 * f(a + h * i);
    }
    sum += f(b);
    return h * sum / 2;
}

void Prob1() {
    const double a = 0, b = 10,
        g = 9.8,  m = 68.1, c = 0.25;

    auto v = [&g, &m, &c](double t) {
        return sqrt(g * m / c) *
            tanh(sqrt(g * c / m) * t);
    };

    std::cout
        << "Problem 1:" << std::endl << std::endl
        << "n = 5    --> s = " << Trapm(v, a, b, 5) << std::endl
        << "n = 10   --> s = " << Trapm(v, a, b, 10) << std::endl
        << "n = 50   --> s = " << Trapm(v, a, b, 50) << std::endl
        << "n = 100  --> s = " << Trapm(v, a, b, 100) << std::endl
        << "n = 500  --> s = " << Trapm(v, a, b, 500) << std::endl
        << "n = 1000 --> s = " << Trapm(v, a, b, 1000) << std::endl
        << std::endl;
}
void Prob2() {
    const std::vector<double> x{0, 30, 60, 90, 120, 150, 180, 210, 240};
    const std::vector<double> y{0, 340, 1200, 1600, 2700, 3100, 3200, 3500, 3800};
    std::cout << "Problem 2: " << Trapm(x, y) << std::endl << std::endl;
}
#pragma endregion

#pragma region Problems 3 and 4
double Trap(double h, double f0, double f1) {
    return h * (f1 + f0) / 2;
}
double Simp38(double h, double f0, double f1, double f2, double f3) {
    return 3 * h * (f0 + 3 * (f1 +  f2) + f3) / 8;
}
double Simp13m(double h, int n, const std::vector<double> y) {
    double sum = y[0];
    for (int i = 1; i < n - 2; i += 2) {
        sum += 4 * y[i] + 2 * y[i + 1];
    }
    sum += 4 * y[n - 1] + y[n];
    return h * sum / 3;
}
double SimpInt(const std::vector<double> y, double h) {
    int n = y.size() - 1;
    if (n == 1) {
        return Trap(h, y[1], y[0]);
    } else {
        double sum = 0;
        int m = n;
        if (n % 2 != 0) {// if we got here n > 1 is a given
            sum += Simp38(h, y[n - 3], y[n - 2], y[n - 1], y[n]);
            m -= 3;
        }
        if (m > 1) { sum += Simp13m(h, m, y); }
        return sum;
    }
}

void Prob3() {
    double a = -2, b = 4, h = 0;
    std::vector<double> y;
    auto f = [](double x) {
        double xpow[6];
        Powers(xpow, 6, x);
        return 1 - x - 4 * xpow[3] + 2 * xpow[5];
    };
    auto make = [&a, &b, &y, &f](int n, double& h) {
        y.resize(n + 1);
        h = (b - a) / n;
        y[0] = f(a);
        for (int i = 1; i < n; ++i) {
            y[i] = f(a + h * i);
        }
        y[n] = f(b);
    };

    std::cout << "Problem 3:" << std::endl << std::endl; make(2, h);
    std::cout << "n = 2  --> I = " << SimpInt(y, h) << std::endl; make(3, h);
    std::cout << "n = 3  --> I = " << SimpInt(y, h) << std::endl; make(4, h);
    std::cout << "n = 4  --> I = " << SimpInt(y, h) << std::endl; make(10, h);
    std::cout << "n = 10 --> I = " << SimpInt(y, h) << std::endl; make(20, h);
    std::cout << "n = 20 --> I = " << SimpInt(y, h) << std::endl << std::endl;
}
void Prob4() {
    const int C = 100000;
    const double h = 0.2;
    const std::vector<double> y{0.2, 0.3683, 0.3819, 0.2282, 0.0486, 0.0082, 0.1441};

    std::cout << "Problem 4: " <<  C * SimpInt(y, h) << std::endl << std::endl;
}
#pragma endregion

#pragma region Problems 5 and 6
void Prob5() {
    const std::vector<double> v{0.5, 2, 3, 4, 6, 8, 10, 11};
    const std::vector<double> p{336, 294.4, 266.4, 260.8, 260.5, 249.6, 193.6, 165.6};
    std::cout << "Problem 5: " << Trapm(v, p) << std::endl << std::endl;
}
void Prob6() {

}
#pragma endregion

void assign5::main() {
    Prob1();
    Prob2();
    Prob3();
    Prob4();
    Prob5();
    Prob6();
}
