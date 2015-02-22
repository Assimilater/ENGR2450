#include "assign3.h"
#include <iostream>
#include <iomanip>

#include "../shared/matrix.h"
using namespace assign3;

void assign3::Problem1() {
    Matrix<double> a{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    std::cout << a[2][1] << std::endl;
}

void assign3::main() {
    Problem1();
}
