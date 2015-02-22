//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Driver for ENGR 2450 homework                                                   |
//---------------------------------------------------------------------------------+
#include "assign1\assign1.h"
#include "assign2\assign2.h"
#include "assign3\assign3.h"
#include "shared\matrix.h"
#include <iostream>

int main() {
    assign3::main();

    Matrix<double> a{{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    std::cout << a[1][1] << std::endl;

    system("pause");
    return 0;
}
