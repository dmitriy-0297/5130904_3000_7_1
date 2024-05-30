#include "shape.h"

using namespace std::placeholders;

namespace dyan {

  bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  bool Point::operator!=(const Point& other) const {
    return !(*this == other);
  }

  bool Point::operator<(const Point& other) const {
    if (x == other.x) return y < other.y;
    return x < other.x;
  }

  bool Polygon::operator==(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    return std::equal(points.begin(), points.end(), other.points.begin());
  }

  bool Polygon::operator<(const Polygon& other) const {
    return area() < other.area();
  }

  double Polygon::area() const {
    double res = 0;
    for (size_t i = 1; i < points.size(); ++i) {
      res += points[i - 1].x * points[i].y - points[i].x * points[i - 1].y;
    }
    res += points.back().x * points.front().y - points.back().y * points.front().x;
    return 0.5 * std::abs(res);
  }

  bool Polygon::is_overlay_compatible(const Polygon& other) const {
    if (points.size() != other.points.size()) return false;
    std::vector<Point> sorted_points(points);
    std::sort(sorted_points.begin(), sorted_points.end());
    double x_offset = other.points[0].x - sorted_points[0].x;
    double y_offset = other.points[0].y - sorted_points[0].y;
    return std::equal(other.points.begin(), other.points.end(), sorted_points.begin(), [x_offset, y_offset](const Point& p1, const Point& p2) {
      return p1.x - p2.x == x_offset && p1.y - p2.y == y_offset;
      });
  }

  std::istream& operator>>(std::istream& in, Point& point) {
    return in >> point.x >> point.y;
  }

  std::ostream& operator<<(std::ostream& out, const Point& point) {
    return out << point.x << " " << point.y;
  }

  std::istream& operator>>(std::istream& in, Polygon& polygon) {
    size_t size;
    in >> size;
    if (size < 3) {
      in.setstate(std::ios::failbit);
      return in;
    }
    polygon.points.resize(size);
    for (auto& point : polygon.points) {
      if (!(in >> point)) {
        in.setstate(std::ios::failbit);
        return in;
      }
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
    out << polygon.points.size() << " ";
    for (const auto& point : polygon.points) {
      out << point << " ";
    }
    return out;
  }

  std::istream& operator>>(std::istream& in, Delimeter&& del) {
    char symbol;
    in >> symbol;
    if (!in || symbol != del.exp) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

}
