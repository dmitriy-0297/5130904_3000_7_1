#include "shape.h"

using namespace std::placeholders;

bool dyan::Point::operator==(const Point& other) const
{
  return x == other.x && y == other.y;
}

bool dyan::Point::operator!=(const Point& other) const
{
  return x != other.x || y != other.y;
}

bool dyan::Point::operator<(const Point& other) const
{
  if (x == other.x) return y < other.y;
  return x < other.x;
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
  auto sorted_point = sorted_points.begin();
  auto testFunc = [&sorted_point, &x_offset, &y_offset](const Point& point)
    {
      bool result = point.x - (*sorted_point).x == x_offset
        && point.y - (*sorted_point).y == y_offset;
      sorted_point++;
      return result;
    };
  return std::all_of(other.points.begin(), other.points.end(), testFunc);
}

std::istream& dyan::operator>>(std::istream& in, dyan::Delimeter&& dest)
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

std::istream& dyan::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> Delimeter{ '(' } >> point.x >> Delimeter{ ';' } >> point.y >> Delimeter{ ')' };
  return in;
}

std::istream& dyan::operator>>(std::istream& in, Polygon& polygon)
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

  polygon.points.clear();
  polygon.points.resize(numPoints);

  for (dyan::Point& point : polygon.points)
  {
    in >> point;
  }
  return in;
}

std::ostream& dyan::operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::ostream& dyan::operator<<(std::ostream& out, const Polygon& polygon)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << polygon.points.size() << " ";

  for (const dyan::Point& p : polygon.points)
  {
    out << p << " ";
  }
  return out;
}
