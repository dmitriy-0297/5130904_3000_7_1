#include "geometry.h"
#include <cmath>
#include <numeric>
#include <iterator>

double anisimov::Point::getDistance(const Point& point) const
{
  double distance = sqrt((x - point.x) * (x - point.x) + (y - point.y) * (y - point.y));
  return distance;
}

bool anisimov::Point::operator !=(const Point& other) const
{
  return x != other.x || y != other.y;
}

double anisimov::getTrigonArea(const Point& point1, const Point& point2, const Point& point3)
{
  double firstSide = point1.getDistance(point2);
  double secondSide = point2.getDistance(point3);
  double thirdSide = point1.getDistance(point3);
  double halfPerimeter = (firstSide + secondSide + thirdSide) / 2;
  double trigonArea = sqrt(halfPerimeter * (halfPerimeter - firstSide) * (halfPerimeter - secondSide) * (halfPerimeter - thirdSide));
  return trigonArea;
}

bool anisimov::Polygon::operator <(const Polygon& other) const
{
  return getArea() < other.getArea();
}

bool anisimov::Polygon::operator ==(const Polygon& other) const
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

double anisimov::Polygon::getArea() const
{
  if (points.size() < 3)
  {
    return 0.0;
  }

  const Point& pointFirst = points[0];
  Point prev = points[1];

  return std::accumulate(points.begin() + 2, points.end(), 0.0,
    [&pointFirst, &prev](double accumulatedArea, const Point& current)
    {
      double trigonArea = getTrigonArea(pointFirst, prev, current);
      accumulatedArea += trigonArea;
      prev = current;
      return accumulatedArea;
    }
  );
}

std::istream& anisimov::operator>>(std::istream& in, anisimov::DelimiterIO&& dest)
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

std::istream& anisimov::operator>>(std::istream& in, anisimov::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> anisimov::DelimiterIO{ '(' } >> point.x >> anisimov::DelimiterIO{ ';' } >> point.y >> anisimov::DelimiterIO{ ')' };
  return in;
}

std::istream& anisimov::operator>>(std::istream& in, anisimov::Polygon& polygon)
{
  size_t numVertices;
  in >> numVertices;

  polygon.points.clear();
  polygon.points.resize(numVertices);

  for (anisimov::Point& point : polygon.points)
  {
    in >> point;
  }

  return in;
}

std::ostream& anisimov::operator<<(std::ostream& out, const anisimov::Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::ostream& anisimov::operator<<(std::ostream& out, const anisimov::Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << polygon.points.size() << " ";

  for (const anisimov::Point& point : polygon.points)
  {
    out << point << " ";
  }

  return out;
}
