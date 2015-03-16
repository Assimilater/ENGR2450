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
        {0, 2, -1},
        {5, 2, 2},
        {-3, 5, -1},
    };
    Matrix<double> ai = a.Inverse(error);

    std::cout
        << (error ? "Error" : "No Error") << std::endl
        << ai << std::endl;

    system("pause");
    return 0;
}
