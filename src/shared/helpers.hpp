#pragma once
#include <vector>
#include <unordered_map>
#include <functional>

void Powers(double*, int, double);
void Power(double, double, std::vector<double>&);

std::unordered_map<double, double> Eulers(std::function<double(double, double)>, double, double, double, double);
