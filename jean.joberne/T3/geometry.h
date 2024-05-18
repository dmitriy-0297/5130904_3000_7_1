#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "local.h"

namespace jean
{
    struct Point
    {
        int x;
        int y;
        double getDistance(const Point& point) const;
        bool operator !=(const Point& other) const;
    };

    double getTrigonArea(const Point& point1, const Point& point2, const Point& point3);

    struct Polygon
    {
        std::vector<Point> points;
        bool operator <(const Polygon& other) const;
        bool operator ==(const Polygon& other) const;
        double getArea() const;
    };

    struct DelimiterIO
    {
        char exp;
    };

    std::istream& operator>>(std::istream& in, jean::DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, jean::Point& point);
    std::istream& operator>>(std::istream& in, jean::Polygon& polygon);
    std::ostream& operator<<(std::ostream& out, const jean::Point& point);
    std::ostream& operator<<(std::ostream& out, const jean::Polygon& polygon);
}

#endif

