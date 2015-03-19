#include "a4p3.hpp"
#include "assign4.hpp"
using namespace assign4;

#include <vector>
#include <iomanip>
#include <functional>

void assign4::Problem3() {
    const_vector y {15.1, 17.9, 12.7, 25.6, 20.5, 35.1, 29.7, 45.4, 40.2};
    const Matrix <double> X {
        {0, 0},
        {1, 1},
        {1, 2},
        {2, 1},
        {2, 2},
        {3, 1},
        {3, 2},
        {4, 1},
        {4, 2},
    };

    bool error = false;
    Matrix<double> Z(X.Rows, X.Cols + 1, [&X](int r, int c) {
        return c == 0 ? 1 : X[r][c - 1];
    });

    std::vector<double>
        a = NLRegress(Z, y, error),
        yf = Z * a;

    std::cout
        << "Problem 3:" << std::endl << std::endl
        << std::setw(3) << "x1"
        << std::setw(4) << "x2"
        << std::setw(6) << "y"
        << std::setw(8) << "yf" << std::endl
        << "-------------------------" << std::endl;

    int n = X.Rows;
    for (int i = 0; i < n; ++i) {
        std::cout
            << std::setw(2) << X[i][0]
            << std::setw(4) << X[i][1]
            << std::setw(8) << y[i]
            << std::setw(10) << yf[i] << std::endl;
    }

    std::cout << std::endl
        << "a: " << a << std::endl << std::endl;
}
