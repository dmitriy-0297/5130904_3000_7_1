#include "shape.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char symb = '0';
  in >> symb;
  if (in && symb != dest.exp) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, IntIO&& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  in >> dest.ref;
  if (!in) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, Polygon& dest) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  Polygon shape;
  size_t nPoints = 0;
  in >> nPoints;
  if (nPoints < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  int temp = 0;
  for (size_t i = 0; i < nPoints; ++i) {
    Point point;
    in >> DelimiterIO{'('};
    in >> IntIO{temp};
    point.x = temp;
    in >> DelimiterIO{';'};
    in >> IntIO{temp};
    point.y = temp;
    in >> DelimiterIO{')'};
    if (in) {
      shape.points.push_back(point);
    }
  }

  if (shape.points.size() == nPoints) {
    dest = shape;
  } else {
    in.setstate(std::ios::failbit);
  }
  return in;
}
