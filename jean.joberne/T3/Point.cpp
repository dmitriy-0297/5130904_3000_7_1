#include "Point.h"

namespace jean {
    std::istream& operator>>(std::istream &in, Point &point) {
        char ignore;
        in >> ignore >> point.x >> ignore >> point.y >> ignore;
        return in;
    }

    std::ostream& operator<<(std::ostream &out, const Point &point) {
        out << "(" << point.x << ";" << point.y << ")";
        return out;
    }
}

