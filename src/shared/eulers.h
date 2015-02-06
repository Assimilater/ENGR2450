#pragma once

#include <unordered_map>
#include <functional>

//---------------------------------------------------------------------------------+
// std::unordered_map<double, double> Eulers                                       |
// Given an arbitrary differential equation, perform Euler's method                |
//---------------------------------------------------------------------------------+
std::unordered_map<double, double> Eulers(
    std::function<double(double, double)> ode,
    double f_init,
    double t_init,
    double t_final,
    double t_inc) {

    double
        t = t_init,
        f = f_init;

    std::unordered_map<double, double> steps;
    steps.insert(std::make_pair(t, f));

    do {
        f += t_inc * ode(t, f);
        t += t_inc;

        steps.insert(std::make_pair(t, f));
    } while (t < t_final);

    return steps;
}
