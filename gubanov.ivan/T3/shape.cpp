#include "shape.h"

double gubanov::Point::getDistance(const Point& point) const
{
  return std::hypot(x - point.x, y - point.y);
}

bool gubanov::Point::operator!=(const Point& other) const
{
  return x != other.x || y != other.y;
}

double gubanov::getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird)
{
  double a = pointFirst.getDistance(pointSecond),
    b = pointSecond.getDistance(pointThird),
    c = pointFirst.getDistance(pointThird);
  double perimeter = (a + b + c) / 2;
  return sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
}

bool gubanov::Polygon::operator<(const Polygon& other) const
{
  return getArea() < other.getArea();
}

bool gubanov::Polygon::operator==(const Polygon& other) const
{
  if (points.size() != other.points.size())
  {
    return false;
  }
  for (size_t i = 0; i < points.size(); i++)
  {
    if (points[i] != other.points[i])
    {
      return false;
    }
  }
  return true;
}

double gubanov::Polygon::getArea() const
{
  const Point pointFirst = points[0];
  Point prev = points[1];
  return std::accumulate(points.begin() + 2, points.end(), 0.0,
    [&pointFirst, &prev](double accumulatedArea, const Point& current)
    {
      double TriangleArea = getTriangleArea(pointFirst, prev, current);
      accumulatedArea += TriangleArea;
      prev = current;
      return accumulatedArea;
    }
  );
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char symbol = '0';

  in >> symbol;

  if (in && (symbol != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> gubanov::DelimeterIO{ '(' } >> point.x >> gubanov::DelimeterIO{ ';' } >> point.y >> gubanov::DelimeterIO{ ')' };
  return in;
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::Polygon& poly)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t numPoints;

  in >> numPoints;

  if (numPoints < 3)
  {
    in.setstate(std::istream::failbit);
    return in;
  }

  poly.points.clear();
  poly.points.resize(numPoints);

  for (gubanov::Point& point : poly.points)
  {
    in >> point;
  }
  return in;
}

std::ostream& gubanov::operator<<(std::ostream& out, const gubanov::Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::ostream& gubanov::operator<<(std::ostream& out, const gubanov::Polygon& poly)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << poly.points.size() << " ";

  for (const gubanov::Point& point : poly.points)
  {
    out << point << " ";
  }
  return out;
}
