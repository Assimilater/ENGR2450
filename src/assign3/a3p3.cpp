#include "a3p3.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#include "../shared/matrix.h"

using namespace assign3;

void assign3::Problem3() {
    Matrix<double> a{
        {1, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    std::vector<double> b{2, 9, 1};
    std::vector<double> x;
    MatrixError error = MatrixError::GOOD;



    // Output the result of Gaussian eleminiation with partial pivoting
    if (error == MatrixError::GOOD) {
        std::cout << "The result is: " << x << std::endl;
    } else if (error == MatrixError::INV_DIM) {
        std::cout << "The matrix a and the solution vector b have invalid dimensions..." << std::endl;
    } else if (error == MatrixError::SINGULAR) {
        std::cout << "The matrix a is singular, and ax = b has no solution..." << std::endl;
    } else {
        std::cout << "An unkown error has occured..." << std::endl;
    }
}
