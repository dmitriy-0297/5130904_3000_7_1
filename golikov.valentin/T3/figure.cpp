#include "figure.h"

double golikov::Point::getDistance(const Point& point) const
{
  return std::hypot(x - point.x, y - point.y);
}

bool golikov::Point::operator != (const Point& other) const
{
  return x != other.x || y != other.y;
}

double golikov::getTriangleArea(const Point& pointFirst, const Point& pointSecond, const Point& pointThird)
{
  double a = pointFirst.getDistance(pointSecond),
    b = pointSecond.getDistance(pointThird),
    c = pointFirst.getDistance(pointThird);
  double perimeter = (a + b + c) / 2;
  return sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
}

bool golikov::Segment::isIntersect(const Segment& other, std::pair<double, double>* intr = nullptr) const
{
  double
    a11 = end.x - begin.x,
    a12 = other.begin.x - other.end.x,
    a21 = end.y - begin.y,
    a22 = other.begin.y - other.end.y,
    dx = other.begin.x - begin.x,
    dy = other.begin.y - begin.y;

  if (a11 == 0 || a11 * a22 - a21 * a12 == 0)
    return false;

  double t2 = (dy * a11 - dx * a21) / (a11 * a22 - a21 * a12);
  double t1 = (dx - a12 * t2) / a11;

  if (t1 < 0 || t2 < 0 || t1 > 1 || t2 > 1)
    return false;

  if (intr != nullptr)
    *intr = std::make_pair(double(begin.x) + (end.x - begin.x) * t1,
      double(begin.y) + (end.y - begin.y) * t1);

  return true;
}

bool golikov::Polygon::contains(const Point& pnt) const
{
  std::vector<int> xArr(points.size());
  std::vector<int> yArr(points.size());

  std::transform(points.begin(), points.end(),
    xArr.begin(), [](const Point& pnt) { return pnt.x; });

  int maxX = *std::max_element(xArr.begin(), xArr.end());

  Point outOfBounds = { maxX + 3, pnt.y };
  Segment ray = { pnt, outOfBounds };
  auto sgmtPool = createSegmentPool();

  std::vector<std::pair<double, double>> intrPoints(points.size());

  auto addPoint = [&ray]
  (const Segment& sgmt)
    {
      std::pair<double, double> res;

      if (sgmt.isIntersect(ray, &res))
        return res;
      return std::make_pair((double)NAN, (double)NAN);
    };

  auto removeCond = []
  (const std::pair<double, double>& p)
    {
      return std::isnan(p.first) || std::isnan(p.second);
    };

  std::transform(sgmtPool.begin(), sgmtPool.end(), intrPoints.begin(), addPoint);
  auto ri = std::remove_if(intrPoints.begin(), intrPoints.end(), removeCond);

  intrPoints.erase(ri, intrPoints.end());
  std::sort(intrPoints.begin(), intrPoints.end());
  auto last = std::unique(intrPoints.begin(), intrPoints.end());
  intrPoints.erase(last, intrPoints.end());

  return intrPoints.size() & 1;
}

std::vector<golikov::Segment> golikov::Polygon::createSegmentPool(void) const
{
  std::vector<Segment> res(points.size());
  Point prev = points[0];

  auto segmentCreator = [&]
  (const Point& cur)
    {
      Segment ans = { prev, cur };

      prev = cur;
      return ans;
    };

  std::transform(points.begin() + 1, points.end(), res.begin(), segmentCreator);
  res.back() = Segment({ points[points.size() - 1], points[0] });

  return res;
}

bool golikov::Polygon::isIntersect(const Polygon& other) const
{
  auto otherSegments = other.createSegmentPool();
  auto ourSegments = createSegmentPool();

  auto countInner = [&]
  (int ac, const Point& pnt)
    {
      return ac + contains(pnt);
    };

  int inner = std::accumulate(other.points.begin(), other.points.end(), 0, countInner);

  if (inner != 0)
    return true;

  auto countIntrOneIter = [&]
  (int ac, const Segment& sgmt)
    {
      auto countIntrNested = [&sgmt]
      (int accum, const Segment& sgmtOther)
        {
          return accum + sgmt.isIntersect(sgmtOther);
        };

      return ac + std::accumulate(otherSegments.begin(), otherSegments.end(), 0, countIntrNested);
    };

  int res = std::accumulate(ourSegments.begin(), ourSegments.end(), 0, countIntrOneIter);

  return res != 0;
}

bool golikov::Polygon::operator < (const Polygon& other) const
{
  return getArea() < other.getArea();
}

bool golikov::Polygon::operator == (const Polygon& other) const
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

double golikov::Polygon::getArea() const
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

std::istream& golikov::operator >> (std::istream& in, golikov::DelimeterIO&& dest)
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

std::istream& golikov::operator >> (std::istream& in, golikov::Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> golikov::DelimeterIO{ '(' } >> point.x >> golikov::DelimeterIO{ ';' } >> point.y >> golikov::DelimeterIO{ ')' };
  return in;
}

std::istream& golikov::operator >> (std::istream& in, golikov::Polygon& poly)
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

  for (golikov::Point& point : poly.points)
  {
    in >> point;
  }
  return in;
}

std::ostream& golikov::operator << (std::ostream& out, const golikov::Point& point)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::ostream& golikov::operator << (std::ostream& out, const golikov::Polygon& poly)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << poly.points.size() << " ";

  for (const golikov::Point& point : poly.points)
  {
    out << point << " ";
  }
  return out;
}
