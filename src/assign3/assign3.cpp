#include "assign3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace assign3;

void assign3::Substitute(
    Matrix<double> &a,
    std::vector<double> &b,
    std::vector<double> &x)
{
    x[a.Rows - 1] = b[a.Rows - 1] / a[a.Rows - 1][a.Cols - 1];
    for (int i = a.Rows - 2; i > -1; --i) {
        double sum = 0;
        for (int j = i + 1; j < a.Rows; ++j) {
            sum += a[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / a[i][i];
    }
}

void assign3::Pivot(
    Matrix<double> &a,
    std::vector<double> &b,
    std::vector<double> &s,
    int k)
{
    int p = k;
    double temp;
    double max = abs(a[k][k] / s[k]);
    for (int i = k + 1; i < a.Rows; ++i) {
        temp = abs(a[i][k] / s[i]);
        if (temp > max) {
            max = temp;
            p = i;
        }
    }

    if (p != k) {
        for (int j = k; j < a.Rows; ++j) {
            temp = a[p][j];
            a[p][j] = a[k][j];
            a[k][j] = temp;
        }

        temp = b[p];
        b[p] = b[k];
        b[k] = temp;

        temp = s[p];
        s[p] = s[k];
        s[k] = temp;
    }
}

void assign3::Eliminate(
    Matrix<double> &a,
    std::vector<double> &b,
    std::vector<double> &s,
    double tolerance,
    GaussError &error)
{
    int k = 0;
    for (; k < a.Rows - 1; ++k) {
        Pivot(a, b, s, k);
        if (abs(a[k][k] / s[k]) < tolerance) {
            // Make sure the diagnals are all non-zero
            error = GaussError::SINGULAR;
            return;
        }

        for (int i = k + 1; i < a.Rows; ++i) {
            double factor = a[i][k] / a[k][k];
            for (int j = k + 1; j < a.Rows; ++j) {
                a[i][j] -= factor * a[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // Not sure what exactly this is checking
    if (abs(a[a.Rows - 1][a.Rows - 1]) < tolerance) {
        error = GaussError::SINGULAR;
    }
}

std::vector<double> assign3::TryGauss(
    Matrix<double> a,
    std::vector<double> &b,
    double tolerance,
    GaussError& error)
{
    if (a.Rows != a.Cols || a.Rows != b.size()) {
        error = GaussError::INV_DIM;
        return b;
    }

    double temp;
    std::vector<double> x(a.Rows), s(a.Rows);

    // Determine the largest coefficient of a in a given column
    for (int i = 0; i < a.Rows; ++i) {
        s[i] = 0;
            for (int j = 0; j < a.Cols; ++j) {
            temp = abs(a[i][j]);
            if (temp > s[j]) {
                s[i] = temp;
            }
        }
    }

    // I have no idea what this does anymore; it's someone else's code
    Eliminate(a, b, s, tolerance, error);
    if (error == GaussError::GOOD) {
        Substitute(a, b, x);
    }

    return x;
}

void assign3::Problem1() {
    Matrix<double> a{
        {1, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    std::vector<double> b{2, 9, 1};
    std::vector<double> x;
    GaussError error = GaussError::GOOD;

    x = TryGauss(a, b, .0001, error);

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
