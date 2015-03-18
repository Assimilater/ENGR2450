#include "a4p1.hpp"
#include <math.h>
#include <vector>
#include <iomanip>
#include <functional>

#include "assign4.hpp"
#include "../shared/matrix.hpp"
using namespace assign4;

std::vector<double> FitData(const_vector x, double m, double b) {
    int n = x.size();
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = m * x[i] + b;
    }
    return y;
}

void PartA(const_vector x, const_vector y) {
    LRegress lReg = Regress(x, y);
    std::vector<double> yf = FitData(x, lReg.m, lReg.b);
    std::cout
        << "Part A:" << std::endl << std::endl
        << "m: " << lReg.m << std::endl
        << "b: " << lReg.b << std::endl
        << "syx: " << lReg.syx << std::endl
        << "r2: " << lReg.r2 << std::endl << std::endl
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

typedef std::function<double(double)> trans;
std::vector<double> PartB(const_vector x, const_vector y, LRegress& lReg, trans x_map, trans y_map) {
    int n = x.size();
    std::vector<double> f_x(n), f_y(n);
    for (int i = 0; i < n; ++i) {
        f_x[i] = x_map(x[i]);
        f_y[i] = y_map(y[i]);
    }

    lReg = Regress(f_x, f_y);
    std::vector<double> fit = FitData(f_x, lReg.m, lReg.b);

    std::cout
        << "m: " << lReg.m << std::endl
        << "b: " << lReg.b << std::endl
        << "syx: " << lReg.syx << std::endl
        << "r2: " << lReg.r2 << std::endl << std::endl
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
    std::vector<double> x {6, 7, 11, 15, 17, 21, 23, 29, 29, 37, 39};
    std::vector<double> y {29, 21, 29, 14, 21, 15, 7, 7, 13, 0, 3};

    // Do Part A
    PartA(x, y);

    // Do Part B
    x = {.75, 2, 3, 4, 6, 8, 8.5};
    y = {1.2, 1.95, 2, 2.4, 2.4, 2.7, 2.6};

    std::cout
        << "Part B:" << std::endl << std::endl
        << "Saturation-Growth Rate" << std::endl;

    // Saturation growth rate
    LRegress lReg;
    double alpha, beta;

    PartB(x, y, lReg,
        [](double x) -> double { return 1 / x; },
        [](double y) -> double { return 1 / y; });

    alpha = 1 / lReg.b;
    beta = lReg.m * alpha;

    std::cout
        << "alpha: " << alpha << std::endl
        << "beta: " << beta << std::endl
        << "y = " << alpha << "x / (" << beta << " + x)" << std::endl
        << std::endl
        << "Power Equation" << std::endl;

    // Power Equation
    PartB(x, y, lReg,
        [](double x) -> double { return log10(x); },
        [](double y) -> double { return log10(y); });

    alpha = pow(10, lReg.b);
    beta = lReg.m;

    std::cout
        << "alpha: " << alpha << std::endl
        << "beta: " << beta << std::endl
        << "y = " << alpha << "x^" << beta << std::endl
        << std::endl;
}
