#ifndef __POLY_H_
#define __POLY_H_

#include <iostream>
#include <vector>

namespace kolpakova
{
  struct Point
  {
    int x, y;

    Point(int x0 = 0, int y0 = 0) : x(x0), y(y0)
    {
    }

    bool operator !=(const Point& other) const
    {
      return x != other.x || y != other.y;
    }
  };

  struct Segment
  {
    Point start, end;

    bool isIntersect(const Segment& other, std::pair<double, double>* intr) const;
  };

  struct Polygon
  {
    std::vector<Point> points;

    bool operator ==(const Polygon& other) const;
    bool operator !=(const Polygon& other) const;
    bool operator <(const Polygon& other) const;

    double area(void) const;
    std::vector<Segment> createSegmentPool(void) const;
    bool contains(const Point& point) const;
    bool isIntersect(const Polygon& other) const;
  };

  struct Sep
  {
    char exp;

    Sep(const char ch) : exp(ch)
    {
    }
  };

  std::istream& operator >>(std::istream& stream, Sep&& res);
  std::istream& operator >>(std::istream& stream, Point& res);
  std::istream& operator >>(std::istream& stream, Polygon& res);
  std::ostream& operator <<(std::ostream& stream, const Point& point);
  std::ostream& operator <<(std::ostream& stream, const Polygon& poly);
}
#endif