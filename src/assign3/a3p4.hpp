#pragma once
#include <vector>
#include "assign3.hpp"
#include "../shared/matrix.hpp"

namespace assign3 {
    namespace p4 {
        Matrix<double> MatrixInverse(Matrix<double>, double, MatrixError&);
    }

    void Problem4();
}
