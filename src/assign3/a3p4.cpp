#include "a3p4.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

#include "../shared/matrix.hpp"

// No need to duplicate code
#include "a3p3.hpp"

using namespace assign3::p4;

Matrix<double> assign3::p4::MatrixInverse(
    Matrix<double> a, // copy by value
    double tolerance,
    MatrixError& error)
{
    if (a.Rows != a.Cols) {
        error = MatrixError::INV_DIM;
        return a;
    }

    int n = a.Rows;
    Matrix<double> ai(a);
    std::vector<double> b(n), x(n), s(n);
    std::vector<int> o(n);

    // I have no idea what this does anymore; it's someone else's code
    assign3::p3::Decompose(a, s, o, tolerance, error);
    if (error == MatrixError::GOOD) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                b[j] = i == j ? 1 : 0;
            }
            assign3::p3::Substitute(a, b, x, o);
            for (int j = 0; j < n; ++j) {
                ai[j][i] = x[j];
            }
        }
    }

    return ai;
}

void assign3::Problem4() {
    Matrix<double> a{
        {1, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    MatrixError error = MatrixError::GOOD;

    Matrix<double> ai = MatrixInverse(a, .0001, error);
    Matrix<double> b = a * ai;

    // Output the inverse and product of the two matricies (identity)
    if (error == MatrixError::GOOD) {
        std::cout << "ai: " << ai << "b = a * ai:" << b;
    } else if (error == MatrixError::INV_DIM) {
        std::cout << "The matrix a and the solution vector b have invalid dimensions..." << std::endl;
    } else if (error == MatrixError::SINGULAR) {
        std::cout << "The matrix a is singular, and ax = b has no solution..." << std::endl;
    } else {
        std::cout << "An unkown error has occured..." << std::endl;
    }
}
