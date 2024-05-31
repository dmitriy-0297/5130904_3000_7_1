#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>
#include "io_format_guard.h"

struct Point {
  int x;
  int y;

  bool operator==(const Point& other) const {
    return (x == other.x) && (y == other.y);
  }
};

struct Shape {
  std::vector<Point> points;
};

struct DelimiterIO {
  char exp;
};

struct IntIO {
  int& ref;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, IntIO&& dest);
std::istream& operator>>(std::istream& in, Shape& dest);

#endif // SHAPE_H
