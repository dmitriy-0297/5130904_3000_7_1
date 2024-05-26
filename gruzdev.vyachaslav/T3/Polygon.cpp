#include "Polygon.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char symb = '0';
  in >> symb;
  if (in && symb != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}


std::istream& operator>>(std::istream& in, intIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> dest.ref;
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}


std::istream& operator>>(std::istream& in, Polygon& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  //    Iofmtguard fmtguard(in);

  Polygon polygon;
  size_t nPoints = 0;
  in >> nPoints;
  if (nPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int temp = 0;
  for (size_t i = 0; i < nPoints; ++i)
  {
    Point point;
    in >> DelimiterIO{ '(' };
    in >> intIO{ temp };
    point.x = temp;
    in >> DelimiterIO{ ';' };
    in >> intIO{ temp };
    point.y = temp;
    in >> DelimiterIO{ ')' };
    if (in)
    {
      polygon.points.push_back(point);
    }
  }

  if (polygon.points.size() == nPoints)
  {
    dest = polygon;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
