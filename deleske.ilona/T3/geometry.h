#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#include <vector>
#include <cmath>
#include <numeric>  // std::accumulate
#include <stdexcept>
#include <algorithm>

namespace deleske
{
  struct Point
  {
    int x, y;
    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool operator<(const Polygon &other) const;
    bool operator==(const Polygon &other) const;
    bool operator!=(const Polygon &other) const;
  };

  struct Frame
  {
    Point lowerLeft;
    Point upperRight;
    Frame(const Point &lowerLeft, const Point &upperRight);
    bool containsPoint(const Point &p) const;
    bool containsPolygon(const Polygon &poly) const;
  };

  struct Triangle
  {
    Point a, b, c;
    Triangle(const Point &a, const Point &b, const Point &c);
    double getArea() const;
  };

  double getDistance(const Point &p1, const Point &p2);
  Frame getFrame(const std::vector<Polygon> &data);
}
#endif
