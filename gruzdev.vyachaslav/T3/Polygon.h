#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <limits>
#include <sstream>

#include "iofmtguard.h"

struct Point
{
  int x;
  int y;

  bool operator ==(const Point& other) const
  {
    return ((other.x == this->x) && (other.y == this->y));
  }
};

struct Polygon
{
  std::vector< Point > points;
};

struct DelimiterIO
{
  char exp;
};

struct intIO
{
  int& ref;
};

struct DelStrIO
{
  std::string exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, intIO&& dest);
std::istream& operator>>(std::istream& in, Polygon& dest);

#endif
