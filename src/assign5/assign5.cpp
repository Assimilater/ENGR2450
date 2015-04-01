#include "assign5.hpp"
#include <functional>
#include <iostream>
#include <vector>
#include <math.h>

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
    double a, b, c;
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
    const std::vector<double> x {0, 30, 60, 90, 120, 150, 180, 210, 240};
    const std::vector<double> y {0, 340, 1200, 1600, 2700, 3100, 3200, 3500, 3800};
    std::cout << "Problem 2: " << Trapm(x, y) << std::endl << std::endl;
}
#pragma endregion

#pragma region Problems 3 and 4
double Trap(double f0, double f1) {
    return (f1 - f0) * (f1 + f0) / 2;
}
double Simp13(double f0, double f1, double f2) {
    return (f2 - f0) * (f0 + 4 * f1 + 4 * f2) / 6;
}
double Simp38(double f0, double f1, double f2, double f3) {
    return (f3 - f0) * (f0 + 3 * f1 + 3 * f2 + f3) / 8;
}
double SimpInt(const std::vector<double> x, const std::vector<double> y) {
    int n = x.size(), segs;
    double sum = 0, h;
    do {

    } while (false);
    return sum;
}

void Prob3() {

}
#pragma endregion

#pragma region Problems 5 and 6
#pragma endregion

void assign5::main() {
    Prob1();
    Prob2();
    //Prob3();
    //Prob4();
    //Prob5();
    //Prob6();
}
