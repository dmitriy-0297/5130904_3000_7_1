#ifndef GEOMETRY_STRUCTS_H
#define GEOMETRY_STRUCTS_H

#include "local.h"

namespace geometry
{
    struct Point
    {
        int x_, y_;
        Point(int x = 0, int y = 0) : x_(x), y_(y) {}
        bool operator!=(const Point& otherEl) const;
    };

    struct Polygon
    {
        std::vector<Point> points;
        double area() const;
        bool operator==(const Polygon& otherEl) const;
    };

    struct DelimIO
    {
        std::string delim_;
        DelimIO(const std::string delim) : delim_(delim) {}
    };

    std::istream& operator>>(std::istream& in, Point& elem);
    std::istream& operator>>(std::istream& in, Polygon& elem);
    std::istream& operator>>(std::istream& in, DelimIO&& elem);
    std::ostream& operator<<(std::ostream& op, const Point& elem);
    std::ostream& operator<<(std::ostream& op, const Polygon& elem);
}

#endif
