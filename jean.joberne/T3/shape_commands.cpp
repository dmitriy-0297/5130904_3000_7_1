#include "shape_commands.h"

int getGaussMultiplication(const Point& p1, const Point& p2)
{
  return (p1.x * p2.y - p1.y * p2.x);
}

double getShapeArea(const Shape& shape)
{
  double area = 0.0;
  size_t size = shape.points.size();
  for (size_t i = 0; i < size; ++i)
  {
    area += getGaussMultiplication(shape.points[i], shape.points[(i + 1) % size]);
  }
  area = std::fabs(area / 2.0);

  return area;
}

void area(std::vector<Shape>& shapes)
{
  std::string mode;
  std::cin >> mode;
  std::cout << std::fixed << std::setprecision(1);

  if (mode == "EVEN" || mode == "ODD")
  {
    bool isEven = (mode == "EVEN");
    double totalArea = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [isEven](double sum, const Shape& shape) {
        if ((shape.points.size() % 2 == 0) == isEven)
        {
          return sum + getShapeArea(shape);
        }
        return sum;
      });
    std::cout << totalArea << std::endl;
  }
  else if (mode == "MEAN")
  {
    if (shapes.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    double totalArea = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double sum, const Shape& shape) {
        return sum + getShapeArea(shape);
      });
    std::cout << (totalArea / shapes.size()) << std::endl;
  }
  else
  {
    int vertexCount = std::stoi(mode);
    if (vertexCount < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    double totalArea = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [vertexCount](double sum, const Shape& shape) {
        if (shape.points.size() == static_cast<size_t>(vertexCount))
        {
          return sum + getShapeArea(shape);
        }
        return sum;
      });
    std::cout << totalArea << std::endl;
  }
}

void max(std::vector<Shape>& shapes)
{
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA")
  {
    if (shapes.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return getShapeArea(a) < getShapeArea(b);
      });
    std::cout << std::fixed << std::setprecision(1);
    std::cout << getShapeArea(*result) << std::endl;
  }
  else if (mode == "VERTEXES")
  {
    if (shapes.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void min(std::vector<Shape>& shapes)
{
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA")
  {
    if (shapes.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return getShapeArea(a) < getShapeArea(b);
      });
    std::cout << std::fixed << std::setprecision(1);
    std::cout << getShapeArea(*result) << std::endl;
  }
  else if (mode == "VERTEXES")
  {
    if (shapes.empty())
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void count(std::vector<Shape>& shapes)
{
  std::string mode;
  std::cin >> mode;

  if (mode == "EVEN")
  {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return shape.points.size() % 2 == 0; }) << std::endl;
  }
  else if (mode == "ODD")
  {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return shape.points.size() % 2 != 0; }) << std::endl;
  }
  else
  {
    int vertexCount = std::stoi(mode);
    if (vertexCount < 3)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [vertexCount](const Shape& shape) { return shape.points.size() == static_cast<size_t>(vertexCount); }) << std::endl;
  }
}

void perms(std::vector<Shape>& shapes)
{
  Shape local;
  std::cin >> local;
  if (!std::cin)
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  else
  {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [&local](const Shape& shape) {
        return std::is_permutation(shape.points.begin(), shape.points.end(),
          local.points.begin(), local.points.end());
      }) << std::endl;
  }
}
