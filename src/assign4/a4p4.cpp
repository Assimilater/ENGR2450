#include "a4p4.hpp"
#include "assign4.hpp"
using namespace assign4;

#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>

//-----------------------------------------------------------------------+
// std::vector<newt_value> NewtInt                                       |
// Return an interpolation from a regession of orders 1 through n        |
//-----------------------------------------------------------------------+
struct newt_val { int order; double yint, error; };
std::vector<newt_val> NewtInt(const_vector& x, const_vector& y, int n, double x0) {
    std::vector<newt_val> set(n);
    Matrix<double> fdd(n, n);

    for (int i = 0; i < n; ++i) {
        set[i].order = i + 1;
        fdd[i][0] = y[i];
    }
    for (int j = 1; j < n; ++j) {
        for (int i = 0; i < n - j; ++i) {
            fdd[i][j] = fdd[i + 1][j - 1] - fdd[i][j - 1];
            fdd[i][j] /= (x[i + j] - x[i]);
        }
    }

    double xterm = 1, yterm;
    set[0].yint = fdd[0][0];

    for (int order = 1; order < n; ++order) {
        xterm *= (x0 - x[order - 1]);
        yterm = set[order - 1].yint + fdd[0][order] * xterm;
        set[order - 1].error = yterm - set[order - 1].yint;
        set[order].yint = yterm;
    }

    return set;
}

//-----------------------------------------------------------------------+
// std::vector<newt_value> NewtInterp                                    |
// Given x-y pairs, select n + 1 optimal points and execute NewtInt      |
// The assignment description said programming this wasn't required,     |
// but I prefer this over manually deteremining the points of interest   |
//-----------------------------------------------------------------------+
struct sort_item { int row; double value; };
std::vector<newt_val> NewtInterp(const_vector& x, const_vector& y, int n, double x0) {
    int count = x.size(), upper = count - 1, lower = 0;
    while (lower + 1 < upper && x[lower + 1] < x0) { ++lower; }
    while (upper - 1 > lower && x[upper - 1] > x0) { --upper; }
    double mid = (upper + lower) / 2.0;

    // Sort [l, r] in ascending order of importance
    // First determined by difference in index from median i
    // Then by difference in sampled x-value from point x0
    auto rank = [&x, x0, mid](const sort_item& l, const sort_item& r) {
        double
            left_dx = abs(l.value - x0),
            right_dx = abs(r.value - x0),
            left_di = abs(mid - l.row),
            right_di = abs(mid - r.row);

        return left_di != right_di ? left_di < right_di : left_dx < right_dx;
    };

    // Sort [l, r] by order of ascending sampled x-values
    // It's expected x and y are initially passed sorted like this
    auto sequential = [](const sort_item& l, const sort_item& r) {
        return l.value < r.value;
    };

    // Sort data by rank
    std::vector<sort_item> diffs;
    for (int i = 0; i < count; ++i) {
        diffs.push_back({i, x[i]});
    }
    sort(diffs.begin(), diffs.end(), rank);

    /* debugging code
    for (auto& elem : diffs) {
        std::cout << "[" << elem.row << "] -> " << elem.value << std::endl;
    }
    std::cout << std::endl;//*/

    // Select n + 1 points and order sequentially
    diffs.resize(n + 1);
    sort(diffs.begin(), diffs.end(), sequential);

    /* debugging code
    for (auto& elem : diffs) {
        std::cout << "[" << elem.row << "] -> " << elem.value << std::endl;
    }
    std::cout << std::endl;//*/

    // Generate reduced vectors to pass to NewtInt
    std::vector<double> x_red(n + 1), y_red(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        x_red[i] = x[diffs[i].row];
        y_red[i] = y[diffs[i].row];

        /* debugging code
        std::cout << x_red[i] << ", " << y_red[i] << std::endl;//*/
    }

    /* debugging code
    std::cout
        << "x_red: " << x_red << std::endl
        << "y_red: " << y_red << std::endl
        << std::endl;//*/

    return NewtInt(x_red, y_red, n, x0);
}

void PrintInterp(const std::vector<newt_val>& values) {
    std::cout
        << std::setw(6) << "order"
        << std::setw(10) << "y(x0)"
        << std::setw(14) << "error" << std::endl
        << "---------------------------------" << std::endl;

    for (auto& elem : values) {
        std::cout
            << std::setw(4) << elem.order
            << std::setw(13) << elem.yint
            << std::setw(15) << elem.error << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void assign4::Problem4() {
    /* debugging code
    const_vector x {1, 4, 6, 5, 3, 1.5, 2.5, 3.5};
    const_vector y {0, 1.3862944, 1.7917595, 1.6094379, 1.0986123, 0.40546411, 0.91629073, 1.2527630};
    PrintInterp(NewtInt(x, y, 8, 2));//*/

    // Part A
    const_vector x {1, 2, 3, 5, 7, 8};
    const_vector y {3, 6, 19, 99, 291, 444};
    std::cout << "Part A: " << std::endl << std::endl;
    PrintInterp(NewtInterp(x, y, 4, 4));

    // Part B
    const_vector i {0.25, 0.75, 1.25, 1.5, 2};
    const_vector v {-0.45, -0.6, 0.7, 1.88, 6};
    std::cout << "Part B: " << std::endl << std::endl;
    PrintInterp(NewtInterp(i, v, 4, 1.15));
}
