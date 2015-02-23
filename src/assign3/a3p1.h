#pragma once
#include <vector>
#include "assign3.h"
#include "../shared/matrix.h"

namespace assign3 {
    namespace p1 {
        void Substitute(Matrix<double>&, std::vector<double>&, std::vector<double>&);
        void Pivot(Matrix<double>&, std::vector<double>&, std::vector<double>&, int);
        void Eliminate(Matrix<double>&, std::vector<double>&, std::vector<double>&, double, MatrixError&);
        std::vector<double> Gauss(Matrix<double>, std::vector<double>&, double, MatrixError&);
    }

    void Problem1();
}
