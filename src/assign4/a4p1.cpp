#include "a4p1.hpp"
#include <math.h>
#include <iomanip>
#include <functional>

using namespace assign4;

std::vector<double> FitData(
    const std::vector<double>& x,
    double m,
    double b)
{
    int n = x.size();
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = m * x[i] + b;
    }
    return y;
}

void PartA(
    const std::vector<double>& x,
    const std::vector<double>& y,
    double& m, double& b,
    double& syx, double& r2)
{
    Regress(x, y, m, b, syx, r2);
    std::vector<double> yf = FitData(x, m, b);
    std::cout
        << "Part A:" << std::endl << std::endl
        << "m: " << m << std::endl
        << "b: " << b << std::endl
        << "syx: " << syx << std::endl
        << "r2: " << r2 << std::endl << std::endl
        << std::setw(4) << "x" << std::setw(6) << "y" << std::setw(8) << "yf" << std::endl
        << "---------------------" << std::endl;

    int n = x.size();
    for (int i = 0; i < n; ++i) {
        std::cout
            << std::setw(4) << x[i]
            << std::setw(6) << y[i]
            << std::setw(10) << yf[i] << std::endl;
    }

    std::cout << std::endl;
}

std::vector<double> PartB(
    const std::vector<double>& x,
    const std::vector<double>& y,
    double& m, double& b,
    double& syx, double& r2,
    std::function<double(double)> x_map,
    std::function<double(double)> y_map)
{
    int n = x.size();
    std::vector<double> f_x(n), f_y(n);
    for (int i = 0; i < n; ++i) {
        f_x[i] = x_map(x[i]);
        f_y[i] = y_map(y[i]);
    }

    Regress(f_x, f_y, m, b, syx, r2);
    std::vector<double> fit = FitData(f_x, m, b);

    std::cout
        << "m: " << m << std::endl
        << "b: " << b << std::endl
        << "syx: " << syx << std::endl
        << "r2: " << r2 << std::endl << std::endl
        << std::setw(3) << "x"
        << std::setw(6) << "y"
        << std::setw(9)  << "f_x"
        << std::setw(10) << "f_y"
        << std::setw(10) << "fit"
        << std::endl
        << "-----------------------------------------" << std::endl;

    for (int i = 0; i < n; ++i) {
        std::cout
            << std::setw(4) << x[i]
            << std::setw(6) << y[i]
            << std::setw(10) << f_x[i]
            << std::setw(10) << f_y[i]
            << std::setw(10) << fit[i]
            << std::endl;
    }

    std::cout << std::endl;
    return fit;
}

void assign4::Problem1() {
    // Common variables
    double m, b, syx, r2, alpha, beta;
    std::vector<double> x {6, 7, 11, 15, 17, 21, 23, 29, 29, 37, 39};
    std::vector<double> y {29, 21, 29, 14, 21, 15, 7, 7, 13, 0, 3};

    // Do Part A
    PartA(x, y, m, b, syx, r2);

    // Do Part B
    x = {.75, 2, 3, 4, 6, 8, 8.5};
    y = {1.2, 1.95, 2, 2.4, 2.4, 2.7, 2.6};

    std::cout
        << "Part B:" << std::endl << std::endl
        << "Saturation-Growth Rate" << std::endl;

    // Saturation growth rate
    PartB(
        x, y, m, b, syx, r2,
        [](double x) -> double { return 1 / x; },
        [](double y) -> double { return 1 / y; });

    alpha = 1 / b;
    beta = m * alpha;

    std::cout
        << "alpha: " << alpha << std::endl
        << "beta: " << beta << std::endl
        << "y = " << alpha << "x / (" << beta << " + x)" << std::endl
        << std::endl
        << "Power Equation" << std::endl;

    // Power Equation
    PartB(
        x, y, m, b, syx, r2,
        [](double x) -> double { return log10(x); },
        [](double y) -> double { return log10(y); });

    alpha = pow(10, b);
    beta = m;

    std::cout
        << "alpha: " << alpha << std::endl
        << "beta: " << beta << std::endl
        << "y = " << alpha << "x^" << beta << std::endl
        << std::endl;
}
