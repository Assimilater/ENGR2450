#include "assign1.h"
#include <iostream>
#include <iomanip>
#include <math.h>

#include "..\shared\eulers.h"
using namespace assign1;

double assign1::singularity(double x, double a, double n) {
    if (x <= a) { return 0; }
    return pow(x - a, n);
}

double assign1::displacement(double x) {
    return
        (-5 * (singularity(x, 0, 4) - singularity(x, 5, 4)) / 6) +
        (15 * singularity(x, 8, 3) / 6) +
        (75 * singularity(x, 7, 2)) +
        (57 * pow(x, 3) / 6) -
        (238.25 * x);
}

void assign1::Problem1() {
    const double
        A = 1200,
        Q = 500,
        alpha = 300,
        Dt = 0.5,
        t_init = 0,
        t_final = 10,
        y_init = 0;

    std::unordered_map<double, double> result = Eulers(
        [A, Q, alpha, Dt, t_init, t_final, y_init](double t, double f) -> double {
        double sin_t = sin(t);
        return 3 * (Q / A) * sin_t * sin_t - (alpha * pow(1 + f, 1.5) / A);
    },
        y_init, t_init, t_final, Dt);

    std::cout
        << "Problem 1:" << std::endl
        << "ODE - A: " << A << std::endl
        << "ODE - Q: " << Q << std::endl
        << "ODE - alpha: " << alpha << std::endl
        << "Euler's Method - dt: " << Dt << std::endl
        << "Euler's Method - t_0: " << t_init << std::endl
        << "Euler's Method - t_f: " << t_final << std::endl
        << "Euler's Method - y_0: " << y_init << std::endl << std::endl
        << "The approximation: " << result[10] << std::endl
        << "--------------------------------------------------" << std::endl << std::endl;
}

void assign1::Problem2() {
    const double
        x_initial = 0,
        x_final = 10,
        x_increment = 0.5;

    std::cout
        << "Problem 2:" << std::endl
        << std::setw(5) << "x" << std::setw(10) << "u(x)" << std::endl;

    for (double x = 0; x <= 10; x += 0.5) {
        std::cout
            << std::setw(5) << x
            << std::setw(10) << displacement(x)
            << std::endl;
    }

    std::cout
        << "--------------------------------------------------" << std::endl << std::endl;
}

void assign1::Problem3() {
    std::streamsize def_precision = std::cout.precision();
    int i = 1, n, max_iterations;
    double x, a, old, error = 100;

    std::cout << "Problem 3:" << std::endl
        << "a: ";
    std::cin >> a;

    std::cout
        << "x_guess: ";
    std::cin >> x;

    std::cout
        << "maxit: ";
    std::cin >> max_iterations;

    std::cout
        << "n: ";
    std::cin >> n;

    double error_criteria = 0.5 * pow(10, 2 - n);

    std::cout << std::endl
        << std::setw(5) << "i" << std::setw(10) << "x" << std::setw(15) << "% error" << std::endl
        << std::setw(5) << i << std::setw(10) << x << std::endl;

    for (i = 2; i < max_iterations && error > error_criteria; ++i) {
        old = x;
        x = (x + (a / x)) / 2;
        error = abs((x - old) / x) * 100;
        std::cout
            << std::setw(5) << i
            << std::setw(10) << x
            << std::setw(14) << std::fixed << std::setprecision(6) << error << "%"
            << std::endl << std::defaultfloat << std::setprecision(def_precision);
    }
}


void assign1::main() {
    Problem1();
    Problem2();
    Problem3();
}
