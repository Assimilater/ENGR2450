#pragma once
#include <vector>
#include "../shared/matrix.hpp"

namespace assign4 {
    typedef const std::vector<double> const_vector;
    struct LRegress { double m, b, syx, r2; };
    LRegress Regress(const_vector&, const_vector&);
    std::vector<double> NLRegress(Matrix<double>, const_vector&, bool&);
    void main();
}
