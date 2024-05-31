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
  auto other_pnt = other.points.begin();
  auto testFunc = [&other_pnt](const Point& pnt)
    {
      bool result = pnt == *other_pnt;
      other_pnt++;
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
  auto testFunc = [&sorted_pnt, &x_offset, &y_offset](const Point& pnt)
    {
      bool result = pnt.x - (*sorted_pnt).x == x_offset
        && pnt.y - (*sorted_pnt).y == y_offset;
      sorted_pnt++;
      return result;
    };
  return std::all_of(other.points.begin(), other.points.end(), testFunc);
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

  for (size_t i = 0; i < size; i++)
  {
    in >> poly.points[i];
  }

  if (in.peek() != int('\n') && !in.eof())
  {
    in.setstate(std::ios::failbit);
    return in;
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