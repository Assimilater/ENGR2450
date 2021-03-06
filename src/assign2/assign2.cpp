#include "assign2.hpp"
#include <iostream>
#include <iomanip>

// Include PI constant
#define _USE_MATH_DEFINES
#include <math.h>

#include "..\shared\helpers.hpp"
#include "..\shared\centered.hpp"
using namespace assign2;

//---------------------------------------------------------------------------------+
// Estimate Bisect                                                                 |
// Given an arbitrary polynomial, use the bisection method to solve                |
// The equation "f(root) = 0", assuming l_bound < root < r_bound                   |
//---------------------------------------------------------------------------------+
Estimate assign2::Bisect(
                std::function<double(double)> f,
                double l_bound,
                double r_bound,
                double max_loops,
                double max_error) {

    Estimate est(l_bound);
    double lSign = f(l_bound);

    if (lSign * f(r_bound) >= 0) {
        std::cout <<
            "Error: left-hand and right-hand estimates do not bound a root" << std::endl;
        return est;
    }

    double prev, sign;
    do {
        ++est.loops;
        prev = est.value;
        est.value = (l_bound + r_bound) / 2;

        if (est.value != 0) {
            est.error = abs(est.value - prev) * 100 / est.value;
        }

        sign = f(est.value) * lSign;
        if (sign < 0) {
            r_bound = est.value;
        } else if (sign > 0) {
            l_bound = est.value;
        } else {
            est.error = 0;
        }
    } while (est.loops < max_loops && est.error >= max_error);

    return est;
}

//---------------------------------------------------------------------------------+
// Estimate ModFalsePos                                                            |
// Given an arbitrary polynomial, use the modified false position method           |
// The equation "f(root) = 0", assuming l_bound < root < r_bound                   |
//---------------------------------------------------------------------------------+
Estimate assign2::ModFalsePos(
                std::function<double(double)> f,
                double l_bound,
                double u_bound,
                double max_loops,
                double max_error) {
    Estimate est(l_bound);
    double fl = f(l_bound);
    double fu = f(u_bound);
    double fr, prev, sign;
    int iu = 0, il = 0; // Horrible names, oh well

    if (fl * fu >= 0) {
        std::cout <<
            "Error: left-hand and right-hand estimates do not bound a root" << std::endl;
        return est;
    }

    do {
        ++est.loops;
        prev = est.value;

        est.value = u_bound - fu * (l_bound - u_bound) / (fl - fu);
        fr = f(est.value);

        if (est.value != 0) {
            est.error = abs(est.value - prev) * 100 / est.value;
        }

        sign = fl * fr;
        if (sign < 0) {
            u_bound = est.value;
            fu = f(u_bound);
            iu = 0;
            ++il;
            if (il >= 2) {
                fl /= 2;
            }
        } else if (sign > 0) {
            l_bound = est.value;
            fl = f(l_bound);
            il = 0;
            ++iu;
            if (iu >= 2) {
                fu /= 2;
            }
        } else {
            est.error = 0;
        }
    } while (est.loops < max_loops && est.error >= max_error);

    return est;
}

//---------------------------------------------------------------------------------+
// Estimate FixedPoint                                                             |
// The function accepted should return x_next given the current estimate of x      |
// Iterate using the fixed point method to approximate an unknown function's root  |
//---------------------------------------------------------------------------------+
Estimate assign2::FixedPoint(
                std::function<double(double)> f,
                double guess,
                double max_loops,
                double max_error) {
    Estimate est(guess);
    double prev;

    do {
        ++est.loops;
        prev = est.value;

        est.value = f(est.value);
        if (est.value != 0) {
            est.error = abs(est.value - prev) * 100 / est.value;
        }
    } while (est.loops < max_loops && est.error >= max_error);

    return est;
}

//---------------------------------------------------------------------------------+
// Problem 1 - Using the Bisection Method                                          |
//---------------------------------------------------------------------------------+
void assign2::Problem1() {
    Estimate est;
    double osf = 8;
    auto polynomial = [&osf](double x) -> double {
        double T_Kelvin[5];
        Powers(T_Kelvin, 5, x + 273.15);

        return log(osf)
            + 139.34411
            - (157570.1 / T_Kelvin[1])
            + (66423080 / T_Kelvin[2])
            - (12438000000 / T_Kelvin[3])
            + (862194900000 / T_Kelvin[4]);
    };

    const int
        TITLE = 50,
        COL_OSF = 10,
        COL_ROOT = 15,
        COL_LOOPS = 10,
        COL_ERROR = 15;

    std::cout << "Problem 1:" << std::endl
        << std::setw(TITLE) << centered("Estimating Roots Between 0-40")
        << std::endl << std::left
        << std::setw(COL_OSF) << "osf"
        << std::setw(COL_ROOT) << "root"
        << std::setw(COL_LOOPS) << "loops"
        << std::setw(COL_ERROR) << "error"
        << std::endl;

    est = Bisect(polynomial, 0, 40, 100, 0.05);
    std::cout
        << std::setw(COL_OSF) << "8"
        << std::setw(COL_ROOT) << est.value
        << std::setw(COL_LOOPS) << est.loops
        << std::setw(COL_ERROR) << est.error
        << std::endl;

    osf = 10;
    est = Bisect(polynomial, 0, 40, 100, 0.05);
    std::cout
        << std::setw(COL_OSF) << "10"
        << std::setw(COL_ROOT) << est.value
        << std::setw(COL_LOOPS) << est.loops
        << std::setw(COL_ERROR) << est.error
        << std::endl;

    osf = 12;
    est = Bisect(polynomial, 0, 40, 100, 0.05);
    std::cout
        << std::setw(COL_OSF) << "12"
        << std::setw(COL_ROOT) << est.value
        << std::setw(COL_LOOPS) << est.loops
        << std::setw(COL_ERROR) << est.error
        << std::endl;

    std::cout << "--------------------------------------------------" << std::endl << std::endl;
}

//---------------------------------------------------------------------------------+
// Problem 2 - Using the Modified False Position Method                            |
//---------------------------------------------------------------------------------+
void assign2::Problem2() {
    const int
        Pu_max = 75000,
        Pu_min = 100000,
        Ps_max = 300000,
        P0 = 10000;
    const double
        ku = .045,
        ks = .08;

    auto Pu = [&Pu_max, &Pu_min, &ku](double t) -> double {
        return Pu_max * exp(-ku * t) + Pu_min;
    };
    auto Ps = [&Ps_max, &P0, &ks](double t) -> double {
        return Ps_max / (1 + ((Ps_max / (P0 - 1)) * exp(-ks * t)));
    };
    auto seek = [&Ps, &Pu](double t) -> double{
        return Ps(t) - 1.2 * Pu(t);
    };

    const int
        TITLE = 70,
        COL_ROOT = 10,
        COL_PVALUE = 15,
        COL_LOOPS = 10,
        COL_ERROR = 15;

    Estimate est;

    std::cout << "Problem 2: Find when Ps = 1.2 Pu"
        << std::endl << std::left
        << std::setw(COL_ROOT) << "t"
        << std::setw(COL_ROOT) << "Ps(t)"
        << std::setw(COL_ROOT) << "Pu(t)"
        << std::setw(COL_PVALUE) << "difference"
        << std::setw(COL_LOOPS) << "loops"
        << std::setw(COL_ERROR) << "error"
        << std::endl;

    est = ModFalsePos(seek, 0, 100, 100, 0.05);
    std::cout
        << std::setw(COL_ROOT) << est.value
        << std::setw(COL_ROOT) << Ps(est.value)
        << std::setw(COL_ROOT) << Pu(est.value)
        << std::setw(COL_PVALUE) << seek(est.value)
        << std::setw(COL_LOOPS) << est.loops
        << std::setw(COL_ERROR) << est.error
        << std::endl;

    std::cout << "----------------------------------------------------------------------" << std::endl << std::endl;
}

//---------------------------------------------------------------------------------+
// Problem 3 - Using the NewtonRaphson Method                                      |
//---------------------------------------------------------------------------------+
void assign2::Problem3() {
    const double guess = 4;
    auto f = [](double h) -> double {
        return M_PI * pow(h, 2) * (9 - h) / 3 - 30;
    };
    auto fp = [](double h) -> double {
        return M_PI * (6 * h - pow(h, 2));
    };

    // The Newton-Raphson method
    auto next = [&f, &fp](double x) -> double {
        return x - (f(x) / fp(x));
    };

    Estimate root = FixedPoint(next, guess, 100, 0.05);
    std::cout
        << "Problem 3:" << std::endl
        << "Root: " << root.value << std::endl
        << "Error: " << root.error << std::endl
        << "Loops: " << root.loops << std::endl
        << std::endl
        << "--------------------------------------------------" << std::endl << std::endl;
}

//---------------------------------------------------------------------------------+
// Problem 4 - Using the Modified Secant Method                                    |
//---------------------------------------------------------------------------------+
void assign2::Problem4() {
    const double
        guess = 4,
        delta = 0.001,
        V = pow(10, 6),
        Q = pow(10, 5),
        W = V,
        k = 0.25;

    auto f = [&V, &Q, &W, &k](double c) -> double {
        return (W / V) - (Q * c / V) - (k * sqrt(c));
    };

    // The modified secant method
    auto next = [&f, &delta](double x) -> double {
        return x - (delta * x * f(x) / (f(x + delta * x) - f(x)));
    };

    Estimate root = FixedPoint(next, guess, 100, 0.05);
    std::cout
        << "Problem 4:" << std::endl
        << "Root: " << root.value << std::endl
        << "Error: " << root.error << std::endl
        << "Loops: " << root.loops << std::endl
        << std::endl
        << "--------------------------------------------------" << std::endl << std::endl;
}

void assign2::main() {
    Problem1();
    Problem2();
    Problem3();
    Problem4();
}
