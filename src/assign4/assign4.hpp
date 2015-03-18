#pragma once
#include <vector>

namespace assign4 {
    typedef const std::vector<double> const_vector;
    struct LRegress { double m, b, syx, r2; };
    LRegress Regress(const_vector&, const_vector&);
    void main();
}
