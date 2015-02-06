#pragma once

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
