#include <algorithm>
#include <numeric>
#include <cmath>
#include <set>

#include "figures.h"

bool kolpakova::Polygon::operator ==(const Polygon& other) const
{
  if (points.size() != other.points.size())
    return false;

  for (size_t i = 0; i < points.size(); i++)
  {
    if (points[i] != other.points[i])
      return false;
  }
  return true;
}

bool kolpakova::Polygon::operator !=(const Polygon& other) const
{
  return !(*this == other);
}

bool kolpakova::Polygon::operator <(const Polygon& other) const
{
  return area() < other.area();
}

bool kolpakova::Segment::isIntersect(const Segment& other, std::pair<double, double>* intr = nullptr) const
{
  double
    a11 = end.x - start.x,
    a12 = other.start.x - other.end.x,
    a21 = end.y - start.y,
    a22 = other.start.y - other.end.y,
    dx = other.start.x - start.x,
    dy = other.start.y - start.y;

  if (a11 == 0 || a11 * a22 - a21 * a12 == 0)
    return false;

  double t2 = (dy * a11 - dx * a21) / (a11 * a22 - a21 * a12);
  double t1 = (dx - a12 * t2) / a11;

  if (t1 < 0 || t2 < 0 || t1 > 1 || t2 > 1)
    return false;

  if (intr != nullptr)
    *intr = std::make_pair(double(start.x) + (end.x - start.x) * t1,
      double(start.y) + (end.y - start.y) * t1);

  return true;
}

double triangleArea(const kolpakova::Point& p1,
  const kolpakova::Point& p2,
  const kolpakova::Point& p3)
{
  double
    a = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)),
    b = sqrt((p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y)),
    c = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
  double p = (a + b + c) / 2;

  return sqrt(p * (p - a) * (p - b) * (p - c));
}

std::vector<kolpakova::Segment> kolpakova::Polygon::createSegmentPool(void) const
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

bool kolpakova::Polygon::contains(const Point& point) const
{
  std::vector<int> xArr(points.size());
  std::vector<int> yArr(points.size());

  std::transform(points.begin(), points.end(), xArr.begin(), [](const Point& point) {
    return point.x;
    });

  int maxX = *std::max_element(xArr.begin(), xArr.end());

  Point outOfBounds = { maxX + 3, point.y };
  Segment ray = { point, outOfBounds };
  auto segmentPool = createSegmentPool();

  std::vector<std::pair<double, double>> intrPoints(points.size());

  auto addPoint = [&ray](const Segment& segment)
    {
      std::pair<double, double> res;

      if (segment.isIntersect(ray, &res))
        return res;
      return std::make_pair((double)NAN, (double)NAN);
    };

  auto removeCond = [](const std::pair<double, double>& p)
    {
      return std::isnan(p.first) || std::isnan(p.second);
    };

  std::transform(segmentPool.begin(), segmentPool.end(), intrPoints.begin(), addPoint);
  auto ri = std::remove_if(intrPoints.begin(), intrPoints.end(), removeCond);

  intrPoints.erase(ri, intrPoints.end());
  std::sort(intrPoints.begin(), intrPoints.end());
  auto last = std::unique(intrPoints.begin(), intrPoints.end());
  intrPoints.erase(last, intrPoints.end());

  return intrPoints.size() & 1;
}

bool kolpakova::Polygon::isIntersect(const Polygon& other) const
{
  auto otherSegments = other.createSegmentPool();
  auto ourSegments = createSegmentPool();

  auto countInner = [&](int ac, const Point& point)
    {
      return ac + contains(point);
    };

  int inner = std::accumulate(other.points.begin(), other.points.end(), 0, countInner);

  if (inner != 0)
    return true;

  auto countIntrOneIter = [&](int ac, const Segment& segment)
    {
      auto countIntrNested = [&segment](int accum, const Segment& segmentOther)
        {
          return accum + segment.isIntersect(segmentOther);
        };

      return ac + std::accumulate(otherSegments.begin(), otherSegments.end(), 0, countIntrNested);
    };

  int res = std::accumulate(ourSegments.begin(), ourSegments.end(), 0, countIntrOneIter);

  return res != 0;
}

double kolpakova::Polygon::area(void) const
{
  const Point p0 = points[0];
  Point prev = points[1];

  auto counter = [&p0, &prev](double ac, const Point& cur)
    {
      ac += triangleArea(p0, prev, cur);
      prev = cur;
      return ac;
    };

  return std::accumulate(points.begin() + 2, points.end(), 0.0, counter);
}
