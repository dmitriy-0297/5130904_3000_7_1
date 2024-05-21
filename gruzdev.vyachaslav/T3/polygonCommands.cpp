#include "polygonCommands.h"

using namespace std::placeholders;

int getGaussMultiplication(const Point& p1, const Point& p2)
{
  return (p1.x * p2.y - p1.y * p2.x);
}

double getArea(const Polygon& polygon)
{
  double area = 0.0;
  size_t size = polygon.points.size();
  for (size_t i = 0; i < size; ++i)
  {
    area += getGaussMultiplication(polygon.points[i], polygon.points[(i + 1) % size]);
  }
  area = std::fabs(area / 2.0);

  return area;
}

void area(std::vector< Polygon >& polygons)
{
  std::string mode;
  std::cin >> mode;
  std::cout << std::fixed << std::setprecision(1);
  if (mode == "EVEN")
  {
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon)
      {
        area += (polygon.points.size() % 2 == 0) ? getArea(polygon) : 0.0;
        return area;
      }) << std::endl;
  }
  else if (mode == "ODD")
  {
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon)
      {
        area += (polygon.points.size() % 2 != 0) ? getArea(polygon) : 0.0;
        return area;
      }) << std::endl;
  }
  else if (mode == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("");
    }
    std::cout << (std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon)
      {
        area += getArea(polygon);
        return area;
      })) / polygons.size() << std::endl;
  }
  else
  {
    size_t size = std::stoull(mode);
    if (size <= 2)
    {
      throw std::invalid_argument("");
    }
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [size](double area, const Polygon& polygon)
      {
        area += (polygon.points.size() == size) ? getArea(polygon) : 0.0;
        return area;
      }) << std::endl;
  }
}

void max(std::vector< Polygon >& polygons)
{
  std::string mode;
  std::cin >> mode;

  if (!polygons.empty() && mode == "AREA")
  {
    std::vector<Polygon>::iterator result;

    result = std::max_element(polygons.begin(), polygons.end(),
      std::bind(std::less<double>{}, std::bind(getArea, _1), std::bind(getArea, _2)));

    std::cout << std::fixed << std::setprecision(1);
    std::cout << getArea(*result) << std::endl;

  }
  else if (!polygons.empty() && mode == "VERTEXES")
  {
    std::vector<Polygon>::iterator result;

    result = std::max_element(polygons.begin(), polygons.end(),
      std::bind(std::less<double>{},
        std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1)),
        std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _2))));


    std::cout << (*result).points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument("");
  }
}

void min(std::vector< Polygon >& polygons)
{
  std::string mode;
  std::cin >> mode;

  if (!polygons.empty() && mode == "AREA")
  {
    std::vector<Polygon>::iterator result;

    result = std::min_element(polygons.begin(), polygons.end(),
      std::bind(std::less<double>{}, std::bind(getArea, _1), std::bind(getArea, _2)));

    std::cout << std::fixed << std::setprecision(1);
    std::cout << getArea(*result) << std::endl;
  }
  else if (!polygons.empty() && mode == "VERTEXES")
  {
    std::vector<Polygon>::iterator result;

    result = std::min_element(polygons.begin(), polygons.end(),
      std::bind(std::less<double>{},
        std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1)),
        std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _2))));

    std::cout << (*result).points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument("");
  }
}

void count(std::vector< Polygon >& polygons)
{
  std::string mode;
  std::cin >> mode;

  if (mode == "EVEN")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& polygon) { return polygon.points.size() % 2 == 0; }) << std::endl;
  }
  else if (mode == "ODD")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& polygon) { return polygon.points.size() % 2 != 0; }) << std::endl;
  }
  else
  {
    size_t size = std::stoi(mode);
    if (size <= 2)
    {
      throw std::invalid_argument("");
    }

    std::cout << std::count_if(polygons.begin(), polygons.end(),
      [size](const Polygon& polygon) { return polygon.points.size() == size; }) << std::endl;
  }
}

void perms(std::vector< Polygon >& polygons)
{
  Polygon local;
  std::cin >> local;
  if (!std::cin)
  {
    throw std::invalid_argument("");
  }
  else
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(),
      [&local](const Polygon& polygon)
      {
        return std::is_permutation(polygon.points.begin(), polygon.points.end(),
        local.points.begin(), local.points.end());
      }) << std::endl;
  }
}

double getDistance(const Point& point1, const Point& point2)
{
  return (sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)));
}

bool isEqualDouble(double x, double y)
{
  return std::fabs(x - y) < pow(10, -5);//std::numeric_limits<double>::epsilon();
}

bool isRightAngledTriangle(const Point& point1, const Point& point2, const Point& point3)
{
  double a = getDistance(point1, point2);
  double b = getDistance(point2, point3);
  double c = getDistance(point1, point3);

  return (isEqualDouble(pow(c, 2), pow(a, 2) + pow(b, 2)),
    isEqualDouble(pow(a, 2), pow(b, 2) + pow(c, 2)),
    isEqualDouble(pow(b, 2), pow(c, 2) + pow(a, 2)));
}

bool hasRightAngle(const Polygon& polygon)
{
  size_t size = polygon.points.size();

  if (size <= 2)
  {
    throw std::invalid_argument("");
  }

  bool result = false;

  for (size_t i = 0; i < size && !result; ++i)
  {
    Point a = polygon.points[i];
    Point b = polygon.points[(i + 1) % size];
    Point c = polygon.points[(i + 2) % size];
    if (isRightAngledTriangle(a, b, c))
    {
      result = true;
    }
  }
  return result;
}

void rightShapes(std::vector< Polygon >& polygons)
{
  std::cout << std::count_if(polygons.begin(), polygons.end()) << std::endl;
}
