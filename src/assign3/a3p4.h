#pragma once
#include <vector>
#include "assign3.h"
#include "../shared/matrix.h"

namespace assign3 {
    namespace p4 {
        Matrix<double> MatrixInverse(Matrix<double>, double, MatrixError&);
    }

    void Problem4();
}
