#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include "Point.h"

namespace jean {
    struct Polygon {
        std::vector<Point> points;

        double area() const;

        bool operator==(const Polygon &other) const;
    };

    std::istream& operator>>(std::istream &in, Polygon &polygon);
    std::ostream& operator<<(std::ostream &out, const Polygon &polygon);
}

#endif // POLYGON_H
