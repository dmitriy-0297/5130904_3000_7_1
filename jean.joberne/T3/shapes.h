#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <string>
#include <vector>

struct Point {
  int x, y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

struct Shape {
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
std::istream& operator>>(std::istream& in, Shape& dest);

#endif // SHAPES_H

