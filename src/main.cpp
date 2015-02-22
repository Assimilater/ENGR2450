//---------------------------------------------------------------------------------+
// John Call - A01283897                                                           |
// Driver for ENGR 2450 homework                                                   |
//---------------------------------------------------------------------------------+
#include "assign1\assign1.h"
#include "assign2\assign2.h"
#include "assign3\assign3.h"
#include "shared\split.h"
#include <iostream>

int main() {
    assign3::main();

    std::string s = "This is a test";
    std::vector<std::string> split = Split(s, ' ');
    for (auto i = split.begin(); i < split.end(); ++i) {
        std::cout << *i << std::endl;
    }

    system("pause");
    return 0;
}
