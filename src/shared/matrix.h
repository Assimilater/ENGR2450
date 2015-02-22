#pragma once
#include <vector>
#include <initializer_list>

template <typename T>
class Matrix {
private:
    T** _array;

public:
    int Rows, Cols;

    // public access to _array
    T* operator [](int r) { return _array[r]; }

    // Constructor to allow for C++11 initializer_list
    Matrix(std::initializer_list<std::initializer_list<T>> s) {
        // Take advantage of vector handling initalizer_list
        std::vector<std::initializer_list<T>> init = s;
        std::vector<std::vector<T>> data;
        for (auto i = init.begin(); i != init.end(); ++i) {
            data.push_back(std::vector<T>(*i));
        }

        Rows = data.size();
        Cols = data[0].size();
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = data[i][j];
            }
        }
    };

    Matrix(int m, int n, T val) {
        Rows = m;
        Cols = n;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = val;
            }
        }
    };

    ~Matrix() {
        for (int i = 0; i < Cols; ++i) {
            delete _array[i];
        }
        delete _array;
        _array = nullptr;
    };
};
