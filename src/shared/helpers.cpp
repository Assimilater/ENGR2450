#include "helpers.hpp"

//---------------------------------------------------------------------------------+
// void Powers                                                                     |
// Populate an array with values such that list[i] = base^i                        |
//---------------------------------------------------------------------------------+
void Powers(double* list, int size, double base) {
    list[0] = 1;
    for (int i = 1; i < size; ++i) {
        list[i] = list[i - 1] * base;
    }
}
void Power(double base, double pow, std::vector<double>& list) {
    int n = list.size(), size = pow + 1;
    if (size > n) { list.resize(size); }
    if (n == 0) { list[0] = 1; }
    for (int i = n; i < size; ++i) {
        list[i] = list[i - 1] * base;
    }
}

//---------------------------------------------------------------------------------+
// std::unordered_map<double, double> Eulers                                       |
// Given an arbitrary differential equation, perform Euler's method                |
//---------------------------------------------------------------------------------+
std::unordered_map<double, double> Eulers(
    std::function<double(double, double)> ode,
    double f_init,
    double t_init,
    double t_final,
    double t_inc)
{
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
