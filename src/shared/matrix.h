#pragma once
#include <vector>
#include <complex>
#include <iostream>
#include <type_traits>
#include <initializer_list>

template <typename T>
class Matrix {
private:
    T** _array;
    static T _default;

public:
    // Important properties
    int Rows, Cols;

    bool isSingular() { return _array == nullptr; };

    static void setDefault(T val) { _default = val; };

    // public access to _array
    T* operator [](int r) { return _array[r]; };

    // friend templates
    template <typename f_T>
    friend std::ostream& operator<<(std::ostream&, const Matrix<f_T>&);

    template <typename f_T>
    friend Matrix<f_T> Transpose(const Matrix<f_T>&);

    template <typename f_T>
    friend f_T Trace(const Matrix<f_T>&, bool&);

    template <typename f_T>
    friend std::vector<f_T> operator*(const Matrix<f_T>&, const std::vector<f_T>&);

    template <typename f_T1, typename f_T2>
    friend Matrix<f_T1> operator*(const Matrix<f_T1>&, const Matrix<f_T2>&);

    template <typename f_T1, typename f_T2>
    friend Matrix<f_T1>& operator+=(Matrix<f_T1>&, const Matrix<f_T2>&);

    // Common operations
    Matrix<T> Transpose() { return Transpose(*this); };
    T Trace() { return Trace(*this); };

    // Constructors and destructor
    Matrix() {
        Rows = 0;
        Cols = 0;
        _array = nullptr;
    };

    Matrix(int m, int n) {
        Rows = m;
        Cols = n;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
        }
    };

    // Allow initialized values
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

    // Allow for C++11 initializer_list
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

    Matrix(const Matrix<T> &a) { copy(a); }
    ~Matrix() { clean(); };

    Matrix<T>& operator=(const Matrix<T> &a) {
        clean();
        copy(a);
        return *this;
    };

private:
    void clean() {
        for (int i = 0; i < Cols; ++i) {
            delete _array[i];
        }
        delete _array;
        _array = nullptr;
    };

    void copy(const Matrix<T> &a) {
        this->Rows = a.Rows;
        this->Cols = a.Cols;
        this->_array = new T*[this->Rows];
        for (int i = 0; i < this->Rows; ++i) {
            this->_array[i] = new T[this->Cols];
            for (int j = 0; j < this->Cols; ++j) {
                this->_array[i][j] = a._array[i][j];
            }
        }
    };
};

template<typename T>
T Matrix<T>::_default = 0;

// iostream handlers
template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &obj) {
    out << "[";
    for (auto i = obj.begin(); i < obj.end(); ++i) {
        out << *i;
        if (i < obj.end() - 1) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

template <typename f_T>
std::ostream& operator<<(std::ostream &out, const Matrix<f_T> &obj) {
    out << std::endl;
    for (int i = 0; i < obj.Rows; ++i) {
        out << "[";
        for (int j = 0; j < obj.Cols; ++j) {
            out << obj._array[i][j];
            if (j < obj.Cols - 1) {
                out << ", ";
            }
        }
        out << "]" << std::endl;
    }
    out << std::endl;
    return out;
}

template <typename f_T>
std::istream& operator>>(std::istream &in, Matrix<f_T> &obj) {
    int m, n;
    in >> m;
    in >> n;
    obj = Matrix<f_T>(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> obj[i][j];
        }
    }
    return in;
}

// common operations
template <typename f_T>
Matrix<f_T> Transpose(const Matrix<f_T> &a) {
    Matrix<f_T> trans(a.Cols, a.Rows);
    for (int i = 0; i < a.Rows; ++i) {
        for (int j = 0; j < a.Cols; ++j) {
            trans[i][j] = a._array[j][i];
        }
    }
    return trans;
}

template <typename f_T>
f_T Trace(const Matrix<f_T> &a, bool& error) {
    f_T sum = a._default;

    if (a.Rows != a.Cols) {
        error = true;
    } else {
        error = false;
        for (int i = 0; i < a.Rows; ++i) {
            sum += a._array[i][i];
        }
    }

    return sum;
}

// syntactical sugar (input validation expected prior to these calls)

// scalar multiplication
template <typename T, typename N,
    typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
Matrix<T> operator*(const N &c, const Matrix<T> &a) {
    Matrix<T> b(a);
    for (int i = 0; i < b.Rows; ++i) {
        for (int j = 0; j < b.Cols; ++j) {
            b[i][j] *= c;
        }
    }
    return b;
}

template <typename T, typename N,
    typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
Matrix<T> operator*(const Matrix<T> &a, const N &c) { return c * a; }

// complex scalar multiplication
template <typename T, typename N, typename C,
    typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<C, std::complex<N>>::value>::type* = nullptr>
Matrix<T> operator*(const C &c, const Matrix<T> &a) {
    Matrix<T> b(a);
    for (int i = 0; i < b.Rows; ++i) {
        for (int j = 0; j < b.Cols; ++j) {
            b[i][j] *= c;
        }
    }
    return b;
}

template <typename T, typename N, typename C,
    typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<C, std::complex<N>>::value>::type* = nullptr>
Matrix<T> operator*(const Matrix<T> &a, const C &c) { return c * a; }

// vector multiplication
template <typename f_T>
std::vector<f_T> operator*(const Matrix<f_T> &a, const std::vector<f_T> &x) {
    std::vector<f_T> b(a.Rows);
    for (int i = 0; i < a.Rows; ++i) {
        b[i] = a._default;
        for (int j = 0; j < a.Cols; ++j) {
            b[i] += a._array[i][j] * x[j];
        }
    }
    return b;
}

// matrix multiplication
template <typename T1, typename T2>
Matrix<T1>& operator*=(Matrix<T1> &a, const Matrix<T2> &b) {
    // Matrix multiplication is more complicated than numeric addition
    // Because 'a' would need to be resized, it is more efficient
    // To use operator* here than to use '*=' in 'operator*'
    return a = a * b;
}

template <typename f_T1, typename f_T2>
Matrix<f_T1> operator*(const Matrix<f_T1> &a, const Matrix<f_T2> &b) {
    Matrix<f_T1> c(a.Rows, b.Cols, a._default);
    for (int i = 0; i < a.Rows; ++i) {
        for (int j = 0; j < a.Cols; ++j) { // a.Cols = b.Rows (or error)
            for (int k = 0; k < b.Cols; ++k) {
                c[i][k] += a._array[i][j] * b._array[j][k];
            }
        }
    }
    return c;
}

// matrix addition
template <typename f_T1, typename f_T2>
Matrix<f_T1>& operator+=(Matrix<f_T1> &a, const Matrix<f_T2> &b) {
    for (int i = 0; i < a.Rows; ++i) {
        for (int j = 0; j < a.Cols; ++j) {
            a._array[i][j] += b._array[i][j];
        }
    }

    return a;
}

template <typename T1, typename T2>
Matrix<T1> operator+(const Matrix<T1> &a, const Matrix<T2> &b) {
    Matrix<T1> c(a);
    c += b;
    return c;
}

// matrix subtraction
template <typename f_T1, typename f_T2>
Matrix<f_T1>& operator-=(Matrix<f_T1> &a, const Matrix<f_T2> &b) {
    for (int i = 0; i < a.Rows; ++i) {
        for (int j = 0; j < a.Cols; ++j) {
            a._array[i][j] -= b._array[i][j];
        }
    }

    return a;
}

template <typename T1, typename T2>
Matrix<T1> operator-(const Matrix<T1> &a, const Matrix<T2> &b) {
    Matrix<T1> c(a);
    c -= b;
    return c;
}
