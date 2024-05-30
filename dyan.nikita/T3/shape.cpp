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
  if (points.size() != other.points.size()) return false;
  auto other_point = other.points.begin();
  auto testFunc = [&other_point](const Point& point)
    {
      bool result = point == *other_point;
      other_point++;
      return result;
    };
  return std::all_of(points.begin(), points.end(), testFunc);
}

bool dyan::Polygon::operator<(const Polygon& other) const
{
  return area() < other.area();
}

double dyan::Polygon::area(void) const
{
  double res = 0;
  for (int i = 1; i < static_cast<int>(points.size()); i++)
  {
    res += points[i - 1].x * points[i].y;
    res -= points[i].x * points[i - 1].y;
  }
  res += (*points.rbegin()).x * (*points.begin()).y;
  res -= (*points.rbegin()).y * (*points.begin()).x;
  return 0.5 * abs(res);
}

bool dyan::Polygon::is_overlay_compatible(const Polygon& other) const
{
  if (points.size() != other.points.size()) return false;
  std::vector<dyan::Point> sorted_points(points);
  std::sort(sorted_points.begin(), sorted_points.end());
  double x_offset = other.points[0].x - sorted_points[0].x;
  double y_offset = other.points[0].y - sorted_points[0].y;
  auto sorted_pnt = sorted_points.begin();
  auto testFunc = [&sorted_pnt, &x_offset, &y_offset](const Point& point)
    {
      bool result = point.x - (*sorted_pnt).x == x_offset
        && point.y - (*sorted_pnt).y == y_offset;
      sorted_pnt++;
      return result;
    };
  return std::all_of(other.points.begin(), other.points.end(), testFunc);
}

std::istream& dyan::operator>>(std::istream& in, Point& point)
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
  in >> Delimeter('(') >> point.x >> Delimeter(';') >> point.y >> Delimeter(')');
  return in;
}

std::ostream& dyan::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(" << point.x << "; " << point.y << ")";
  return out;
}

std::istream& dyan::operator>>(std::istream& in, Polygon& polygon)
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
  polygon.points.clear();
  polygon.points.resize(size);

  for (auto& point : polygon.points)
  {
    in >> point;
  }

  if (in.peek() != '\n' && !in.eof())
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& dyan::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << polygon.points.size() << " ";
  for (const auto& p : polygon.points)
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
  char symbol;
  in >> symbol;

  if (!in || symbol != del.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
