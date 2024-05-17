
#ifndef POINT_H
#define POINT_H

#include <iostream>

namespace jean {
    struct Point {
        int x, y;
        Point(int x = 0, int y = 0) : x(x), y(y) {}
        bool operator!=(const Point &other) const {
            return x != other.x || y != other.y;
        }
        friend std::istream& operator>>(std::istream &in, Point &point);
        friend std::ostream& operator<<(std::ostream &out, const Point &point);
    };

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

#endif // POINT_H

