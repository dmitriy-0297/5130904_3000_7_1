#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "local.h"

namespace anisimov
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

  std::istream& operator>>(std::istream& in, anisimov::DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, anisimov::Point& point);
  std::istream& operator>>(std::istream& in, anisimov::Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const anisimov::Point& point);
  std::ostream& operator<<(std::ostream& out, const anisimov::Polygon& polygon);
}

#endif
