#include "matrix.h"

Matrix<double> Identity(int n) {
    Matrix<double> a(n, n, 0);
    for (int i = 0; i < n; ++i) {
        a[i][i] = 1;
    }
    return a;
}
