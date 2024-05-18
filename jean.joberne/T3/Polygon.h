#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <cmath>
#include <iostream>
#include "Point.h"

namespace jean {
    struct Polygon {
        std::vector<Point> points;

        Polygon() = default;

        double area() const {
            double accum = 0.0;
            for (size_t i = 0; i < points.size(); ++i) {
                const auto &current = points[i];
                const auto &next = points[(i + 1) % points.size()];
                accum += (current.x * next.y - next.x * current.y);
            }
            return std::abs(accum * 0.5);
        }

        bool operator==(const Polygon &other) const {
            if (points.size() != other.points.size()) return false;
            for (size_t i = 0; i < points.size(); ++i) {
                if (points[i] != other.points[i]) return false;
            }
            return true;
        }

        friend std::istream& operator>>(std::istream &in, Polygon &polygon);
        friend std::ostream& operator<<(std::ostream &out, const Polygon &polygon);
    };

    std::istream& operator>>(std::istream &in, Polygon &polygon);
    std::ostream& operator<<(std::ostream &out, const Polygon &polygon);
}

#endif // POLYGON_H

