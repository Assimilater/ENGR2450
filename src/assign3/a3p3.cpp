#include "a3p3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#include "../shared/matrix.h"

using namespace assign3::p3;

void assign3::p3::Substitute(
    Matrix<double> &a,
    std::vector<double> &b,
    std::vector<double> &x,
    std::vector<int> &o)
{
    for (int i = 1; i < a.Rows; ++i) {
        double sum = b[o[i]];
        for (int j = 0; j <= i - 1; ++j) {
            sum -= a[o[i]][j] * b[o[j]];
        }
        b[o[i]] = sum;
    }

    x[a.Rows - 1] = b[o[a.Rows - 1]] / a[o[a.Rows - 1]][a.Rows - 1];
    for (int i = a.Rows - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < a.Rows; ++j) {
            sum += a[o[i]][j] * x[j];
        }
        x[i] = (b[o[i]] - sum) / a[o[i]][i];
    }
}

void assign3::p3::Pivot(
    Matrix<double> &a,
    std::vector<double> &s,
    std::vector<int> &o,
    int k)
{
    int p = k;
    double temp;
    double max = abs(a[o[k]][k] / s[o[k]]);
    for (int i = k + 1; i < a.Rows; ++i) {
        temp = abs(a[o[i]][k] / s[o[i]]);
        if (temp > max) {
            max = temp;
            p = i;
        }
    }

    int t_int = o[p];
    o[p] = o[k];
    o[k] = t_int;
}

void assign3::p3::Decompose(
    Matrix<double> &a,
    std::vector<double> &s,
    std::vector<int> &o,
    double tolerance,
    MatrixError &error)
{
    for (int i = 0; i < a.Rows; ++i) {
        double temp;
        o[i] = i;
        s[i] = abs(a[i][0]);
        for (int j = 1; j < a.Rows; ++j) {
            temp = abs(a[i][j]);
            if (temp > s[i]) {
                s[i] = temp;
            }
        }
    }

    int k = 0;
    for (; k < a.Rows - 1; ++k) {
        Pivot(a, s, o, k);
        if (abs(a[o[k]][k] / s[o[k]]) < tolerance) {
            error = MatrixError::SINGULAR;
            // print a[o[k]][k] / s[o[k]]
            return;
        }

        for (int i = k + 1; i < a.Rows; ++i) {
            double factor = a[o[i]][k] / a[o[k]][k];
            a[o[i]][k] = factor;
            for (int j = k + 1; j < a.Rows; ++j) {
                a[o[i]][j] -= factor * a[o[k]][j];
            }
        }
    }

    // Not sure what exactly this is checking
    if (abs(a[o[k]][k] / s[o[k]]) < tolerance) {
        error = MatrixError::SINGULAR;
        // print a[o[k]][k] / s[o[k]]
    }
}

std::vector<double> assign3::p3::LuDecomp(
    Matrix<double> a,
    std::vector<double> &b,
    double tolerance,
    MatrixError& error)
{
    if (a.Rows != a.Cols || a.Rows != b.size()) {
        error = MatrixError::INV_DIM;
        return b;
    }

    std::vector<double> x(a.Rows), s(a.Rows);
    std::vector<int> o(a.Rows);

    // I have no idea what this does anymore; it's someone else's code
    Decompose(a, s, o, tolerance, error);
    if (error == MatrixError::GOOD) {
        Substitute(a, b, x, o);
    }

    return x;
}

void assign3::Problem3() {
    Matrix<double> a{
        {1, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    std::vector<double> b{2, 9, 1};
    std::vector<double> x;
    MatrixError error = MatrixError::GOOD;

    x = LuDecomp(a, b, .0001, error);

    // Output the result of LU Decomposition
    if (error == MatrixError::GOOD) {
        std::cout << "The result is: " << x << std::endl;
    } else if (error == MatrixError::INV_DIM) {
        std::cout << "The matrix a and the solution vector b have invalid dimensions..." << std::endl;
    } else if (error == MatrixError::SINGULAR) {
        std::cout << "The matrix a is singular, and ax = b has no solution..." << std::endl;
    } else {
        std::cout << "An unkown error has occured..." << std::endl;
    }
}
