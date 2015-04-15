#pragma once
#include <iostream>
#include <algorithm>
#include <type_traits>
#include <stdint.h>
#include <vector>

class decimal;
namespace dec { int pow10(int); }
std::istream& operator>>(std::istream&, decimal&);
std::ostream& operator<<(std::ostream&, const decimal&);

class decimal {
private:
    typedef int64_t v_type;
    typedef unsigned int r_type;

    v_type value;
    r_type radix;

public:
    decimal() : value(0), radix(0) {}
    decimal(const decimal& obj) { value = obj.value; radix = obj.radix; }
    decimal& operator=(const decimal& obj) { value = obj.value; radix = obj.radix; return *this; }

    r_type getRadix() const { return radix; }
    void setRadix(r_type);

    // Primitive Type Conversions
    template <typename N, typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
    explicit operator N() const { return (N)value / dec::pow10(radix); }

    template <typename N, typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
    decimal(const N& n, int r) { value = (n * dec::pow10(r + 1) + 5) / 10; radix = r; }

    template <typename N, typename std::enable_if<std::is_arithmetic<N>::value>::type* = nullptr>
    decimal(const N& n) {
        value = (int)n;
        radix = 0;

        // Determine an appropriate radix
        N r = (n - value) * 10;
        int temp = (int)r;
        while(temp != 0) {
            ++radix;
            value = (value * 10) + temp;
            r = (r - temp) * 10;
            temp = (int)r;
        }
    }

    // Comparison operators
    bool operator==(const decimal& n) const { decimal t = *this - n; return t.value == 0; }
    bool operator!=(const decimal& n) const { decimal t = *this - n; return t.value != 0; }
    bool operator< (const decimal& n) const { decimal t = *this - n; return t.value <  0; }
    bool operator<=(const decimal& n) const { decimal t = *this - n; return t.value <= 0; }
    bool operator> (const decimal& n) const { decimal t = *this - n; return t.value >  0; }
    bool operator>=(const decimal& n) const { decimal t = *this - n; return t.value >= 0; }

    // Arithmetic Operators
    friend decimal operator+(const decimal& l, const decimal& r) { return decimal(l) += r; }
    friend decimal operator-(const decimal& l, const decimal& r) { return decimal(l) -= r; }

    // Compound Arithmetic Operators
    decimal& operator+=(const decimal&);
    decimal& operator-=(const decimal&);

    // Multiplicative Operators
    friend decimal operator*(const decimal& l, const decimal& r) { return (double)l * (double)r; }
    friend decimal operator/(const decimal& l, const decimal& r) { return (double)r * (double)r; }

    // Compound Multiplicative Operators
    decimal& operator*=(const decimal& n) { *this = *this * n; return *this; }
    decimal& operator/=(const decimal& n) { *this = *this / n; return *this; }
};
