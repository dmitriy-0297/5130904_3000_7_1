#include "figures.h"

double kalashnikova::Point::getDistance(const Point& point) const
{
    double distance = 0;
    distance = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
    return distance;
}

bool kalashnikova::Point::operator !=(const Point& other) const
{
    return x != other.x or y != other.y;
}

double kalashnikova::getTrigonArea(const Point& point1, const Point& point2, const Point& point3)
{
    double firstSide = point1.getDistance(point2);
    double secondSide = point2.getDistance(point3);
    double thirdSide = point1.getDistance(point3);
    double halfPerimeter = (firstSide + secondSide + thirdSide) / 2;
    double trigonArea = 0;
    trigonArea = sqrt(halfPerimeter * (halfPerimeter - firstSide) * (halfPerimeter - secondSide) * (halfPerimeter - thirdSide));
    return trigonArea;
}

bool kalashnikova::Polygon::operator <(const Polygon& other) const
{
    return getArea() < other.getArea();
}

bool kalashnikova::Polygon::operator ==(const Polygon& other) const
{
    if (points.size() != other.points.size())
    {
        return false;
    }
    for (size_t i = 0; i < points.size(); i++)
    {
        if (points[i] != other.points[i])
        {
            return false;
        }
    }
    return true;
}

double kalashnikova::Polygon::getArea() const
{
    const Point pointFirst = points[0];
    Point prev = points[1];
    return std::accumulate(points.begin() + 2, points.end(), 0.0, [&pointFirst, &prev](double accumulatedArea, const Point& current)
        {
            double trigonArea = getTrigonArea(pointFirst, prev, current);
            accumulatedArea += trigonArea;
            prev = current;
            return accumulatedArea;
        }
    );
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char null = '0';
    in >> null;
    if (in && (null != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Point& point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> kalashnikova::DelimiterIO{ '(' } >> point.x >> kalashnikova::DelimiterIO{ ';' } >> point.y >> kalashnikova::DelimiterIO{ ')' };
    return in;
}

std::istream& kalashnikova::operator>>(std::istream& in, kalashnikova::Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    size_t amountPoints;
    in >> amountPoints;
    if (amountPoints < 3)
    {
        in.setstate(std::istream::failbit);
        return in;
    }

    polygon.points.clear();
    polygon.points.resize(amountPoints);

    for (kalashnikova::Point& point : polygon.points)
    {
        in >> point;
    }

    return in;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Point& point)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }
    out << "(" << point.x << ";" << point.y << ")";
    return out;
}

std::ostream& kalashnikova::operator<<(std::ostream& out, const kalashnikova::Polygon& polygon)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    out << polygon.points.size() << " ";

    for (const kalashnikova::Point& point : polygon.points)
    {
        out << point << " ";
    }

    return out;
}
