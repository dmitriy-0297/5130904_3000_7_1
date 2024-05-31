#ifndef SHAPE_H
#define SHAPE_H

#include "local.h"

namespace dyan
{
  struct Point
  {
    int x, y;
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    bool operator<(const Point& other) const;
  };

  struct Polygon
  {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
    bool operator<(const Polygon& other) const;
    double area(void) const;
    bool isOverlayCompatible(const Polygon& other) const;
  };

  struct Delimeter
  {
    char exp;

    Delimeter(const char exp) : exp(exp)
    {
    }
  };

  std::istream& operator>>(std::istream& in, Delimeter&& del);
  std::istream& operator>>(std::istream& in, Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
