#include "assign4.hpp"
#include "a4p1.hpp"
#include "a4p2.hpp"
#include "a4p3.hpp"
#include "a4p4.hpp"

#include "../shared/matrix.hpp"
using namespace assign4;

//-----------------------------------------------------------------------+
// LRegress Regress                                                      |
// Determine the coefficients for the linear regression of y = mx + b    |
//-----------------------------------------------------------------------+
LRegress assign4::Regress(const_vector& x, const_vector& y) {
    LRegress lReg;
    double
        sumx = 0, sumy = 0,
        sumxy = 0, sumx2 = 0,
        st = 0, sr = 0;

    int n = x.size();
    for (int i = 0; i < n; ++i) {
        sumx += x[i];
        sumy += y[i];
        sumxy += x[i] * y[i];
        sumx2 += x[i] * x[i];
    }

    double xm = sumx / n;
    double ym = sumy / n;
    lReg.m = (n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx);
    lReg.b = ym - lReg.m * xm;

    for (int i = 0; i < n; ++i) {
        st += (y[i] - ym) * (y[i] - ym);
        sr += (y[i] - lReg.m * x[i] - lReg.b) * (y[i] - lReg.m * x[i] - lReg.b);
    }

    lReg.syx = sqrt(sr / (n - 2));
    lReg.r2 = (st - sr) / st;

    return lReg;
}

//-----------------------------------------------------------------------+
// std::vector<double> NLRegress                                         |
// Determine the coefficients for systems with many variables            |
//-----------------------------------------------------------------------+
std::vector<double> assign4::NLRegress(Matrix<double> Z, const_vector& y, bool& e) {
    if (y.size() != Z.Rows) { e = true; return y; }
    Matrix<double> ZT = Z.Transpose();
    Matrix<double> ZI = Inverse(ZT * Z, e);
    if (e) { return y; }
    return ZI * (ZT * y);
}

void assign4::main() {
    //Problem1();
    //Problem2();
    //Problem3();
    Problem4();
}
