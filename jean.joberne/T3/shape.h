#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>
#include "io_format_guard.h"

struct Point
{
  int x;
  int y;

  bool operator==(const Point& other) const
  {
    return (other.x == this->x) && (other.y == this->y);
  }
};

struct Shape
{
  std::vector<Point> points;
};

struct DelimiterIO
{
  char expectedDelimiter;
};

struct IntIO
{
  int& reference;
};

struct DelStrIO
{
  std::string expectedDelimiter;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, IntIO&& dest);
std::istream& operator>>(std::istream& in, Shape& dest);

#endif
