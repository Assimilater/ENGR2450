#pragma once
#include <vector>
#include "assign3.hpp"
#include "../shared/matrix.hpp"

namespace assign3 {
    namespace p3 {
        void Substitute(Matrix<double>&, std::vector<double>&, std::vector<double>&, std::vector<int>&);
        void Pivot(Matrix<double>&, std::vector<double>&, std::vector<int>&, int);
        void Decompose(Matrix<double>&, std::vector<double>&, std::vector<int>&, double, MatrixError&);
        std::vector<double> LuDecomp(Matrix<double>, std::vector<double>&, double, MatrixError&);
    }

    void Problem3();
}
