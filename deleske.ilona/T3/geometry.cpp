#include "geometry.h"

deleske::Triangle::Triangle(const Point &a, const Point &b, const Point &c)
{
  this->a = a;
  this->b = b;
  this->c = c;
}

deleske::Frame deleske::getFrame(const std::vector<Polygon> &data)
{
  if (data.size() == 0)
    throw std::runtime_error("Error: no one Polygon");

  deleske::Point lowerLeft = data[0].points[0];
  deleske::Point upperRight = data[0].points[0];
  for (const deleske::Polygon &poly : data)
  {
    for (const deleske::Point &p : poly.points)
    {
      if (p.x < lowerLeft.x)
        lowerLeft.x = p.x;
      if (p.x > upperRight.x)
        upperRight.x = p.x;
      if (p.y < lowerLeft.y)
        lowerLeft.y = p.y;
      if (p.y > upperRight.y)
        upperRight.y = p.y;
    }
  }
  return deleske::Frame(lowerLeft, upperRight);
}

double deleske::getDistance(const deleske::Point &p1, const deleske::Point &p2)
{
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

double deleske::Triangle::getArea() const
{
  double x = getDistance(a, b);
  double y = getDistance(a, c);
  double z = getDistance(b, c);
  double p = (x + y + z) / 2;
  return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

double deleske::Polygon::getArea() const
{
  deleske::Point fixed = points[0], first = points[1];

  double square = std::accumulate(
      points.begin() + 2,
      points.end(),
      0.0,
      [fixed, &first](double accumulator, deleske::Point second)
      {
        accumulator += Triangle(fixed, first, second).getArea();
        first = second;
        return accumulator;
      }
  );
  return square;
}

bool deleske::Polygon::operator<(const Polygon &other) const
{
  return getArea() < other.getArea();
}

bool deleske::Polygon::operator==(const Polygon &other) const
{
  if (points.size() == other.points.size())
  {
    for (std::size_t i = 0; i < points.size(); ++i)
    {
      if (points[i] != other.points[i])
        return false;
    }
    return true;
  }
  return false;
}

bool deleske::Polygon::operator!=(const Polygon &other) const
{
  return !(*this == other);
}

bool deleske::Point::operator==(const Point &other) const
{
  return x == other.x && y == other.y;
}

bool deleske::Point::operator!=(const Point &other) const
{
  return !(*this == other);
}

deleske::Frame::Frame(const Point &lowerLeft, const Point &upperRight)
{
  if (lowerLeft.x > upperRight.x || lowerLeft.y > upperRight.y)
    throw std::invalid_argument("Invalid frame");

  this->lowerLeft = lowerLeft;
  this->upperRight = upperRight;
}

bool deleske::Frame::containsPoint(const Point &p) const
{
  return p.x >= lowerLeft.x && p.x <= upperRight.x && p.y >= lowerLeft.y && p.y <= upperRight.y;
}

bool deleske::Frame::containsPolygon(const Polygon &poly) const
{
  return std::all_of(poly.points.begin(), poly.points.end(),
                     [this](const Point &p) { return containsPoint(p); });
}
