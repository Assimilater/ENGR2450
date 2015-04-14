#pragma once
#include <algorithm>
#include <type_traits>
#include <stdint.h>
#include <vector>

namespace dec {
    int pow10(int pow) {
        static std::vector<int> list{1, 10, 100, 1000, 10000, 100000, 1000000};
        static int n = list.size() - 1;
        while (n < pow) {
            list.push_back(10 * list[n - 1]); ++n;
        }
        return list[pow];
    }
}

class decimal {
private:
    int64_t value;
    unsigned int radix;

public:
    decimal() : value(0), radix(0) {}
    decimal(const decimal& obj) { value = obj.value; radix = obj.radix; }
    decimal& operator=(const decimal& obj) { value = obj.value; radix = obj.radix; return *this; }

    double getValue() const { double v(value); return v / dec::pow10(radix); }
    int getRadix() const { return radix; }
    void setRadix(unsigned int r) {
        if (r > radix) { value *= dec::pow10(r - radix); radix = r; }
        if (r < radix) { value = ((value / dec::pow10(radix + 1 - r)) + 5) / 10; radix = r; }
    }

    // Convert constructors
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
            value *= 10;

            value += temp;
            r = (r - temp) * 10;
            temp = (int)r;
        }
    }

    // Comparison operators
    bool operator==(const decimal& n) const { decimal t(n); t.setRadix(radix); return value == t.value; }
    bool operator!=(const decimal& n) const { decimal t(n); t.setRadix(radix); return value != t.value; }
    bool operator<(const decimal& n) const { decimal t(n); t.setRadix(radix); return value < t.value; }
    bool operator<=(const decimal& n) const { decimal t(n); t.setRadix(radix); return value <= t.value; }
    bool operator>(const decimal& n) const { decimal t(n); t.setRadix(radix); return value > t.value; }
    bool operator>=(const decimal& n) const { decimal t(n); t.setRadix(radix); return value >= t.value; }

    // Compound Arithmetic operators
    decimal& operator+=(const decimal& n) {
        if (n.radix > radix) { setRadix(n.radix); }
        value += n.value * dec::pow10(radix - n.radix);
        return *this;
    }
    decimal& operator-=(const decimal& n) {
        if (n.radix > radix) { setRadix(n.radix); }
        value -= n.value * dec::pow10(radix - n.radix);
        return *this;
    }

    // Arithmetic Operators
    decimal operator+(const decimal& n) const { decimal t(*this); return t += n; }
    decimal operator-(const decimal& n) const { decimal t(*this); return t -= n; }
};
