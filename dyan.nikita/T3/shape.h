#ifndef SHAPE_H
#define SHAPE_H

#include "local.h"

namespace dyan
{
  struct Point
  {
    int x = 0;
    int y = 0;
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
    bool is_overlay_compatible(const Polygon& other) const;
  };

  struct Delimeter
  {
    char exp;

    Delimeter(const char expected) : exp(expected)
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
