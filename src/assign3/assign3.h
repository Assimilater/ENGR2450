#pragma once
#include <vector>
#include "../shared/matrix.h"

namespace assign3 {
    enum GaussError {
        GOOD = 0,
        INV_DIM = 1,
        SINGULAR = 2
    };

    std::vector<double> TryGauss(Matrix<double>&, std::vector<double>, double, GaussError&);

    void Problem1();
    void main();
}
