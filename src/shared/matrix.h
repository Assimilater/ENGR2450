#pragma once
#include <vector>
#include <initializer_list>

template <typename T>
class Matrix {
public:
    T** value;
    int rows, cols;

    Matrix(std::initializer_list<std::initializer_list<T>> s) {
        // Take advantage of vector handling initalizer_list
        std::vector<std::initializer_list<T>> init = s;
        std::vector<std::vector<T>> data;
        for (auto i = init.begin(); i != init.end(); ++i) {
            data.push_back(std::vector<T>(*i));
        }

        rows = data.size();
        cols = data[0].size();
        value = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            value[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                value[i][j] = data[i][j];
            }
        }
    };

    Matrix(int m, int n, T val) {
        rows = m;
        cols = n;
        value = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            value[i] = new T[cols];
            for (int j = 0; j < cols; ++j) {
                value[i][j] = val;
            }
        }
    };

    ~Matrix() {
        for (int i = 0; i < cols; ++i) {
            delete value[i];
        }
        delete value;
        value = nullptr;
    };
};
