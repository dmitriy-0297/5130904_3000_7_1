#include "Point.h"

namespace jean {
    bool Point::operator==(const Point &other) const {
        return x_ == other.x_ && y_ == other.y_;
    }

    bool Point::operator!=(const Point &other) const {
        return !(*this == other);
    }

    std::istream& operator>>(std::istream &in, Point &point) {
        char ch1, ch2, ch3;
        int x, y;
        if (in >> ch1 >> x >> ch2 >> y >> ch3 && ch1 == '(' && ch2 == ';' && ch3 == ')') {
            point = Point(x, y);
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << '(' << point.x_ << ';' << point.y_ << ')';
        return out;
    }
}

