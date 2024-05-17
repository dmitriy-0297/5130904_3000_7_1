#ifndef POINT_H
#define POINT_H

#include <iostream>

namespace jean {
    struct Point {
        int x_, y_;

        Point(int x = 0, int y = 0) : x_(x), y_(y) {}

        bool operator==(const Point &other) const;  // Declaration of operator==
        bool operator!=(const Point &other) const;
    };

    std::istream& operator>>(std::istream &in, Point &point);
    std::ostream& operator<<(std::ostream &out, const Point &point);
}

#endif // POINT_H

