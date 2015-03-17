#include "a4p1.hpp"
#include <iomanip>
using namespace assign4;
using namespace assign4::p1;

std::vector<double> assign4::p1::FitData(
    const std::vector<double>& x,
    double m,
    double b) {
    int n = x.size();
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = m * x[i] + b;
    }
    return y;
}

void assign4::Problem1() {
    double m, b, syx, r2;

    std::vector<double> x {6, 7, 11, 15, 17, 21, 23, 29, 29, 37, 39};
    std::vector<double> y {29, 21, 29, 14, 21, 15, 7, 7, 13, 0, 3};

    Regress(x, y, m, b, syx, r2);
    std::vector<double> yf = FitData(x, m, b);

    std::cout
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
