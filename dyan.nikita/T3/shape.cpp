#include "shape.h"

using namespace std::placeholders;

bool dyan::Point::operator==(const Point& other) const
{
  return x == other.x && y == other.y;
}

bool dyan::Point::operator!=(const Point& other) const
{
  return !(*this == other);
}

bool dyan::Point::operator<(const Point& other) const
{
  return (x == other.x) ? (y < other.y) : (x < other.x);
}

bool dyan::Polygon::operator==(const Polygon& other) const
{
  return points.size() == other.points.size()
    && std::equal(points.begin(), points.end(), other.points.begin());
}

bool dyan::Polygon::operator<(const Polygon& other) const
{
  return area() < other.area();
}

double dyan::Polygon::area(void) const
{
  double res = 0;
  auto size = static_cast<int>(points.size());
  for (int i = 0; i < size; ++i)
  {
    const Point& current = points[i];
    const Point& next = points[(i + 1) % size];
    res += current.x * next.y;
    res -= next.x * current.y;
  }
  return 0.5 * std::abs(res);
}

bool dyan::Polygon::is_overlay_compatible(const Polygon& other) const
{
  if (points.size() != other.points.size()) return false;

  std::vector<dyan::Point> sorted_points(points);
  std::sort(sorted_points.begin(), sorted_points.end());
  double x_offset = other.points[0].x - sorted_points[0].x;
  double y_offset = other.points[0].y - sorted_points[0].y;

  for (size_t i = 0; i < sorted_points.size(); ++i)
  {
    if ((other.points[i].x - sorted_points[i].x != x_offset)
      || (other.points[i].y - sorted_points[i].y != y_offset))
    {
      return false;
    }
  }
  return true;
}

std::istream& dyan::operator>>(std::istream& in, Point& pnt)
{
  if (in.peek() == '\n')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimeter('(') >> pnt.x >> Delimeter(';') >> pnt.y >> Delimeter(')');
  return in;
}

std::ostream& dyan::operator<<(std::ostream& out, const Point& pnt)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << pnt.x << "; " << pnt.y << ")";
  return out;
}

std::istream& dyan::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t size;
  in >> size;
  if (size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  poly.points.clear();
  poly.points.resize(size);

  for (auto& point : poly.points)
  {
    in >> point;
  }

  if (in.peek() != '\n' && !in.eof())
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& dyan::operator<<(std::ostream& out, const Polygon& poly)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << poly.points.size() << " ";
  for (const auto& p : poly.points)
  {
    out << p << " ";
  }
  return out;
}

std::istream& dyan::operator>>(std::istream& in, Delimeter&& del)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c;
  in >> c;

  if (!in || c != del.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
