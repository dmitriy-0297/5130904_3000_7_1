#include "geometry.h"

double jean::getDistance(const Point& p1, const Point& p2)
{
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

double jean::Polygon::getArea() const
{
    const Point& fixed = points[0];
    Point first = points[1];

    double square = std::accumulate(points.begin() + 2, points.end(), 0.0,
        [&fixed, &first](double accumulator, const Point& second)
        {
            double a = getDistance(fixed, first);
            double b = getDistance(first, second);
            double c = getDistance(second, fixed);
            double s = (a + b + c) / 2;
            accumulator += std::sqrt(s * (s - a) * (s - b) * (s - c));
            first = second;
            return accumulator;
        });

    return square;
}

bool jean::Polygon::operator<(const Polygon& other) const
{
    return getArea() < other.getArea();
}

bool jean::Polygon::operator==(const Polygon& other) const
{
    return points == other.points;
}

bool jean::Polygon::operator!=(const Polygon& other) const
{
    return !(*this == other);
}

bool jean::Point::operator==(const Point& other) const
{
    return x == other.x && y == other.y;
}

bool jean::Point::operator!=(const Point& other) const
{
    return !(*this == other);
}

