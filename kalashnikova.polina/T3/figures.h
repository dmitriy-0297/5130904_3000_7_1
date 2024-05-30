#ifndef FIGURES_H
#define FIGURES_H

#include "local.h"

namespace kalashnikova
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

    std::istream& operator>>(std::istream& in, kalashnikova::DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, kalashnikova::Point& point);
    std::istream& operator>>(std::istream& in, kalashnikova::Polygon& polygon);
    std::ostream& operator<<(std::ostream& out, const kalashnikova::Point& point);
    std::ostream& operator<<(std::ostream& out, const kalashnikova::Polygon& polygon);
}

#endif

