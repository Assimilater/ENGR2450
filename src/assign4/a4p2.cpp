#include "a4p2.hpp"
#include "assign4.hpp"
using namespace assign4;

#include <math.h>
#include <vector>
#include <iomanip>
#include <functional>
#include "../shared/matrix.hpp"

std::vector<double> NLRegress(Matrix<double> Z, const_vector& y, bool& e) {
    if (y.size() != Z.Rows) { e = true; return y; }
    Matrix<double> ZT = Z.Transpose();
    Matrix<double> ZI = Inverse(ZT * Z, e);
    if (e) { return y; }
    return ZI * (ZT * y);
}

void PrintFit(const_vector& x, const_vector& y, int power) {
    bool error = false;
    Matrix<double>Z(x.size(), power + 1, [&x](int r, int c) {
        return pow(x[r], c);
    });

    std::vector<double>
        a = NLRegress(Z, y, error),
        yf = Z * a;

    std::cout
        << std::setw(4) << "x"
        << std::setw(6) << "y"
        << std::setw(8) << "yf" << std::endl
        << "---------------------" << std::endl;

    int n = x.size();
    for (int i = 0; i < n; ++i) {
        std::cout
            << std::setw(4) << x[i]
            << std::setw(6) << y[i]
            << std::setw(10) << yf[i] << std::endl;
    }

    std::cout << std::endl
        << "y = " << a[0] << " + " << a[1] << "x";
    for (int i = 2; i < power + 1; ++i) {
        std::cout << " + " << a[i] << "x^" << i;
    }
    std::cout << std::endl << std::endl;
}

void assign4::Problem2() {
    std::vector<double> x, y;
    std::cout << "Problem 2:" << std::endl;

    // Part A
    x = {0.2, 0.5, 0.8, 1.2, 1.7, 2, 2.3};
    y = {500, 700, 1000, 1200, 2200, 2650, 3750};
    std::cout << "Part A:" << std::endl << std::endl;
    PrintFit(x, y, 2);

    // Part B
    x = {0, 5, 10, 15, 20, 25, 30};
    y = {12.9, 11.3, 10.1, 9.03, 8.17, 7.46, 6.85};
    std::cout << "Part B:" << std::endl << std::endl;
    PrintFit(x, y, 3);
}
