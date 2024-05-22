#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

struct Point {
  int x, y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

struct Polygon {
  std::vector<Point> points;
};

struct DelimiterIO {
  char exp;
};

struct intIO {
  int& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, intIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

#endif

