#ifndef SHAPE_H
#define SHAPE_H

#include "local.h"

namespace gubanov
{
  struct Point
  {
    int x, y;
    double getDistance(const Point& point) const;
    bool operator !=(const Point& other) const;
  };

  double getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird);

  struct Polygon
  {
    std::vector<Point> points;
    bool operator <(const Polygon& other) const;
    bool operator==(const Polygon& other) const;
    double getArea() const;
  };

  struct DelimeterIO
  {
    char exp;
  };

  struct FrameRectangle
  {
    Point bottom_left;
    Point top_right;
  };

  std::istream& operator>>(std::istream& in, gubanov::DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, gubanov::Point& point);
  std::istream& operator>>(std::istream& in, gubanov::Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const gubanov::Point& point);
  std::ostream& operator<<(std::ostream& out, const gubanov::Polygon& poly);
}

#endif
