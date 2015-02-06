#pragma once
#include <functional>

namespace assign2 {
    struct Estimate {
        double error;
        double value;
        int loops;
        Estimate(double est = 0) {
            error = 100;
            loops = 0;
            value = est;
        }
    };

    Estimate Bisect(std::function<double(double)>, double, double, double, double);
    Estimate ModFalsePos(std::function<double(double)>, double, double, double, double);

    void Problem1();
    void Problem2();
    void Problem3();

    void main();
}
