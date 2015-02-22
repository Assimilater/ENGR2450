#include "assign3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace assign3;

std::vector<double> assign3::TryGauss(
    Matrix<double> &a,
    std::vector<double>b,
    double tolerance,
    GaussError& error)
{
    if (a.Rows != a.Cols != b.size()) {
        error = GaussError::INV_DIM;
        return b;
    }

    std::vector<double> x, s;
    double temp;
    for (int i = 0; i < a.Rows; ++i) {
        s[i] = 0;
        for (int j = 0; j < a.Cols; ++j) {
            temp = abs(a[i][j]);
            if (temp > s[i]) {
                s[i] = temp;
            }
        }
    }

    return x;
}

/*
1 2  2       4
1 2  1       
1 2

*/

void assign3::Problem1() {
    Matrix<double> a{
        {1, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    std::vector<double> b{2, 9, 1};
    std::vector<double> x;
    GaussError error = GaussError::GOOD;

    x = TryGauss(a, b, .001, error);

    // Output the result of Gaussian eleminiation with partial pivoting
    if (error == GaussError::GOOD) {
        std::cout << "The result is: " << x << std::endl;
    } else if (error == GaussError::INV_DIM) {
        std::cout << "The matrix a and the solution vector b have invalid dimensions..." << std::endl;
    } else if (error == GaussError::SINGULAR) {
        std::cout << "The matrix a is singular, and ax = b has no solution..." << std::endl;
    } else {
        std::cout << "An unkown error has occured..." << std::endl;
    }
}

void assign3::main() {
    Problem1();
}
