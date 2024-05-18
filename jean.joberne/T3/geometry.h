#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <algorithm>

namespace jean
{
    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
    };

    struct Polygon
    {
        std::vector<Point> points;
        double getArea() const;
        bool operator<(const Polygon& other) const;
        bool operator==(const Polygon& other) const;
        bool operator!=(const Polygon& other) const;
    };

    double getDistance(const Point& p1, const Point& p2);
}

#endif

