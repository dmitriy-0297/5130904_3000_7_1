#ifndef POLYGON_H
#define POLYGON_H

#include <cstddef>
#include <vector>
#include <istream>

namespace dyan
{
  struct Point
  {
    long long x_;
    long long y_;
  };

  struct Polygon
  {
    std::vector< Point > points_;
  };

  bool operator==(const Point& lhs, const Point& rhs);
  bool operator==(const Polygon& lhs, const Polygon& rhs);

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}

#endif
