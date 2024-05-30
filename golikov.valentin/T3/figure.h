#ifndef FIGURE_H
#define FIGURE_H

#include "local.h"

namespace golikov
{
  struct Point
  {
    int x, y;
    double getDistance(const Point& point) const;
    bool operator !=(const Point& other) const;
  };

  double getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird);

  struct Segment
  {
    Point begin, end;

    bool isIntersect(const Segment& other, std::pair<double, double>* intr) const;
  };

  struct Polygon
  {
    std::vector<Point> points;
    bool operator <(const Polygon& other) const;
    bool operator==(const Polygon& other) const;
    double getArea() const;
    bool contains(const Point& pnt) const;
    std::vector<Segment> createSegmentPool(void) const;
    bool isIntersect(const Polygon& other) const;
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

  std::istream& operator >> (std::istream& in, golikov::DelimeterIO&& dest);
  std::istream& operator >> (std::istream& in, golikov::Point& point);
  std::istream& operator >> (std::istream& in, golikov::Polygon& poly);
  std::ostream& operator << (std::ostream& out, const golikov::Point& point);
  std::ostream& operator << (std::ostream& out, const golikov::Polygon& poly);
}

#endif
