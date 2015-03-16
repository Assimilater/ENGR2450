#pragma once
#include <vector>
#include <complex>
#include <iostream>
#include <type_traits>
#include <initializer_list>

template <typename T>
class Matrix {
private:
    T** _array = nullptr;
    static T _default;

public:
    // Important properties
    int Rows = 0, Cols = 0;

    bool isSingular() { return _array == nullptr; };

    static void setDefault(T val) { _default = val; };

    // public access to _array
    T* operator [](int r) { return _array[r]; };

    // Common operations (implemented externally
    Matrix<T> Inverse(bool&) const;
    Matrix<T> Transpose() const;
    T Trace(bool&) const;

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

    // Override default constructors, operator=, and destructor
    Matrix(int m, int n) { init(m, n, _default); };
    Matrix(int m, int n, T val) { init(m, n, val); };
    Matrix<T>& operator=(const Matrix<T> &a) { copy(a); return *this; };
    Matrix(const Matrix<T> &a) { copy(a); }
    ~Matrix() { clean(); };

private:
    void clean() {
        if (_array != nullptr) {
            for (int i = 0; i < Rows; ++i) {
                delete[] _array[i];
            }

            delete[] _array;
        }

        _array = nullptr;
        Rows = 0;
        Cols = 0;
    };

    void init(int m, int n, T val) {
        clean();
        Rows = m;
        Cols = n;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = val;
            }
        }
    }

    void copy(const Matrix<T> &a) {
        clean();
        Rows = a.Rows;
        Cols = a.Cols;
        _array = new T*[Rows];
        for (int i = 0; i < Rows; ++i) {
            _array[i] = new T[Cols];
            for (int j = 0; j < Cols; ++j) {
                _array[i][j] = a._array[i][j];
            }
        }
    };

public:
    // friend templates
    template <typename f_T>
    friend std::ostream& operator<<(std::ostream&, const Matrix<f_T>&);

    template <typename f_T>
    friend std::vector<f_T> operator*(const Matrix<f_T>&, const std::vector<f_T>&);

    template <typename f_T1, typename f_T2>
    friend Matrix<f_T1> operator*(const Matrix<f_T1>&, const Matrix<f_T2>&);

    template <typename f_T1, typename f_T2>
    friend Matrix<f_T1>& operator+=(Matrix<f_T1>&, const Matrix<f_T2>&);
};

// Placeholder for template static member
template<typename T>
T Matrix<T>::_default = 0;

// common operations and helpers
template <typename T>
Matrix<T> Inverse(const Matrix<T> &a, bool& e) { return a.Inverse(e); }

template <typename T>
Matrix<T> Transpose(const Matrix<T> &a) { return a.Transpose(); }

template <typename T>
T Trace(const Matrix<T> &a, bool& e) { return a.Trace(e); }

template <typename T>
Matrix<T> Matrix<T>::Inverse(bool& error) const {
    int n = Rows;
    Matrix<T> left(*this);
    if (!(error = n != Cols)) {
        Matrix<T> right(n, n, 0);
        T temp;
        T *r_temp = new T[n],
          *l_temp = new T[n];

        // Make right the Identity Matrix
        for (int i = 0; i < n; ++i) {
            right[i][i] = 1;
        }

        for (int col = 0; col < n; ++col) {
            // pivot so left[col][col] is non-zero
            int pivot = col;
            while (left[pivot][col] == 0) {
                if (++pivot >= n) {
                    error = true;
                    delete[] r_temp;
                    delete[] l_temp;
                    return left;
                }
            }

            // basic swap of rows between two matricies
            if (pivot != col) {
                for (int i = 0; i < n; ++i) {
                    l_temp[i] = left[pivot][i];
                    r_temp[i] = right[pivot][i];

                    left[pivot][i] = left[col][i];
                    right[pivot][i] = right[col][i];

                    left[col][i] = l_temp[i];
                    right[col][i] = r_temp[i];
                }
            }

            // Nomralize the row so left[col][col] = 1
            temp = left[col][col];
            for (int i = 0; i < n; ++i) {
                left[col][i] /= temp;
                right[col][i] /= temp;
            }

            // Subsitute up and down
            for (int row = 0; row < n; ++row) {
                if (row != col) {
                    temp = left[row][col];
                    for (int i = 0; i < n; ++i) {
                        left[row][i] -= temp * left[col][i];
                        right[row][i] -= temp * right[col][i];
                    }
                }
            }
        }

        // Verify the identity matrix is resulting
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (left[i][j] != (i == j ? 1 : 0)) {
                    error = true;
                    delete[] r_temp;
                    delete[] l_temp;
                    return left;
                }
            }
        }

        delete[] r_temp;
        delete[] l_temp;
        return right;
    }

    return left;
}

template <typename T>
Matrix<T> Matrix<T>::Transpose() const {
    Matrix<T> trans(Cols, Rows);
    for (int i = 0; i < Rows; ++i) {
        for (int j = 0; j < Cols; ++j) {
            trans[j][i] = _array[i][j];
        }
    }
    return trans;
}

template <typename T>
T Matrix<T>::Trace(bool& error) const {
    T sum = _default;

    if (!(error = Rows != Cols)) {
        for (int i = 0; i < Rows; ++i) {
            sum += _array[i][i];
        }
    }

    return sum;
}

// iostream handlers
template <typename T>
std::istream& operator>>(std::istream &in, Matrix<T> &obj) {
    int m, n;
    in >> m;
    in >> n;
    obj = Matrix<T>(m, n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> obj[i][j];
        }
    }
    return in;
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
template <typename N1, typename C, typename N2, typename T,
    typename std::enable_if<std::is_arithmetic<N1>::value>::type* = nullptr,
    typename std::enable_if<std::is_arithmetic<N2>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<C, std::complex<N1>>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<T, std::complex<N2>>::value>::type* = nullptr>
Matrix<T> operator*(const C &c, const Matrix<T> &a) {
    Matrix<T> b(a);
    for (int i = 0; i < b.Rows; ++i) {
        for (int j = 0; j < b.Cols; ++j) {
            b[i][j] *= c;
        }
    }
    return b;
}

template <typename N1, typename C, typename N2, typename T,
    typename std::enable_if<std::is_arithmetic<N1>::value>::type* = nullptr,
    typename std::enable_if<std::is_arithmetic<N2>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<C, std::complex<N1>>::value>::type* = nullptr,
    typename std::enable_if<std::is_same<T, std::complex<N2>>::value>::type* = nullptr>
Matrix<T> operator*(const Matrix<T> &a, const C &c) { return c * a; }
