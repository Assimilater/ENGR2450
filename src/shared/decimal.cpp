#include "decimal.hpp"

int dec::pow10(int pow) {
    static std::vector<int> list{1, 10, 100, 1000, 10000, 100000, 1000000};
    static int n = list.size() - 1;
    while (n < pow) {
        list.push_back(10 * list[n - 1]); ++n;
    }
    return list[pow];
}

std::istream& operator>>(std::istream& in, decimal& obj) {
    double d;
    in >> d;
    obj = d;
    return in;
}

std::ostream& operator<<(std::ostream& out, const decimal& obj) {
    out << (double)obj;
    return out;
}

void decimal::setRadix(r_type r) {
    if (r > radix) { value *= dec::pow10(r - radix); radix = r; }
    if (r < radix) { value = ((value / dec::pow10(radix + 1 - r)) + 5) / 10; radix = r; }
}


decimal& decimal::operator+= (const decimal& n) {
    if (n.radix > radix) { setRadix(n.radix); }
    value += n.value * dec::pow10(radix - n.radix);
    return *this;
}
decimal& decimal::operator-=(const decimal& n) {
    if (n.radix > radix) { setRadix(n.radix); }
    value -= n.value * dec::pow10(radix - n.radix);
    return *this;
}
