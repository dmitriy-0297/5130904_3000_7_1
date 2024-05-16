#include "Point.h"

namespace jean {
    bool Point::operator!=(const Point &other) const {
        return x_ != other.x_ || y_ != other.y_;
    }

    std::istream& operator>>(std::istream &in, Point &point) {
        char ch;
        if (in >> ch && ch == '(' && in >> point.x_ && in >> ch && ch == ';' && in >> point.y_ && in >> ch && ch == ')') {
            return in;
        }
        in.setstate(std::ios_base::failbit);
        return in;
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "(" << point.x_ << ";" << point.y_ << ")";
        return out;
    }
}
