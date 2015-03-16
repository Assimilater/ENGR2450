//-----------------------------------------------------------------------+
// John Call - A01283897                                                 |
// Driver for ENGR 2450 homework                                         |
//-----------------------------------------------------------------------+
#include "assign3\assign3.h"
#include "shared\matrix.h"
#include <iostream>

int main() {
    //assign3::main();
    bool error = false;
    Matrix<double> a{
        {1, 0.2, 0.04},
        {1, 0.5, 0.25},
        {1, 0.8, 0.64},
        {1, 1.2, 1.44},
        {1, 1.7, 2.89},
        {1, 2, 4},
        {1, 2.3, 5.29},
    };
    Matrix<double> at = a.Transpose();
    Matrix<double> ata = at * a;
    Matrix<double> atai = Inverse(ata, error);

    std::cout
        << (error ? "Error" : "No Error") << std::endl
        << a << std::endl
        << at << std::endl
        << ata << std::endl
        << atai << std::endl;

    system("pause");
    return 0;
}
