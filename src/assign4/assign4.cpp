#include "assign4.h"
#include "a4p1.h"

#include "../shared/matrix.h"
using namespace assign4;

//-----------------------------------------------------------------------+
// void Regress                                                          |
// Determine the coefficients for the linear regression of y = mx + b    |
//-----------------------------------------------------------------------+
void assign4::Regress(
    std::vector<double> x,
    std::vector<double> y,
    double& m,
    double& b,
    double& syx,
    double& r2) {
    double sumx = 0,
        sumy = 0,
        sumxy = 0,
        sumx2 = 0,
        st = 0,
        sr = 0;

    int n = x.size();
    for (int i = 0; i < n; ++i) {
        sumx += x[i];
        sumy += y[i];
        sumxy += x[i] * y[i];
        sumx2 += x[i] * x[i];
    }

    double xm = sumx / n;
    double ym = sumy / n;
    m = (n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx);
    b = ym - m * xm;

    for (int i = 0; i < n; ++i) {
        st += (y[i] - ym) * (y[i] - ym);
        sr += (y[i] - m * x[i] - b) * (y[i] - m * x[i] - b);
    }

    syx = sqrt(sr / (n - 2));
    r2 = (st - sr) / st;
}


void assign4::main() {
    Problem1();

    return;
    bool error = false;
    const Matrix<double> a{
        {1, 0.2, 0.04},
        {1, 0.5, 0.25},
        {1, 0.8, 0.64},
        {1, 1.2, 1.44},
        {1, 1.7, 2.89},
        {1, 2, 4},
        {1, 2.3, 5.29},
    };
    Matrix<double> at = a.Transpose();
    Matrix<double> ata = at * a;
    Matrix<double> atai = Inverse(ata, error);

    std::cout
        << (error ? "Error" : "No Error") << std::endl
        << a << std::endl
        << at << std::endl
        << ata << std::endl
        << atai << std::endl;
}
