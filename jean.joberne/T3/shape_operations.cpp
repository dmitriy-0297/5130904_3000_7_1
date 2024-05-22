#include "shape_operations.h"

int getGaussMultiplication(const Point& p1, const Point& p2) {
  return (p1.x * p2.y - p1.y * p2.x);
}

double getArea(const Shape& shape) {
  double area = 0.0;
  size_t size = shape.points.size();
  for (size_t i = 0; i < size; ++i) {
    area += getGaussMultiplication(shape.points[i], shape.points[(i + 1) % size]);
  }
  area = std::fabs(area / 2.0);
  return area;
}

void area(std::vector<Shape>& shapes) {
  std::string mode;
  std::cin >> mode;
  std::cout << std::fixed << std::setprecision(1);
  if (mode == "EVEN") {
    std::cout << std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double area, const Shape& shape) {
        return area + (shape.points.size() % 2 == 0 ? getArea(shape) : 0.0);
      }) << std::endl;
  } else if (mode == "ODD") {
    std::cout << std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double area, const Shape& shape) {
        return area + (shape.points.size() % 2 != 0 ? getArea(shape) : 0.0);
      }) << std::endl;
  } else if (mode == "MEAN") {
    if (shapes.empty()) {
      throw std::invalid_argument("No shapes available");
    }
    double totalArea = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double area, const Shape& shape) {
        return area + getArea(shape);
      });
    std::cout << totalArea / shapes.size() << std::endl;
  } else {
    size_t size = std::stoull(mode);
    if (size <= 2) {
      throw std::invalid_argument("Invalid shape size");
    }
    std::cout << std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [size](double area, const Shape& shape) {
        return area + (shape.points.size() == size ? getArea(shape) : 0.0);
      }) << std::endl;
  }
}

void max(std::vector<Shape>& shapes) {
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA") {
    if (shapes.empty()) {
      throw std::invalid_argument("No shapes available");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return getArea(a) < getArea(b);
      });
    std::cout << std::fixed << std::setprecision(1) << getArea(*result) << std::endl;
  } else if (mode == "VERTEXES") {
    if (shapes.empty()) {
      throw std::invalid_argument("No shapes available");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  } else {
    throw std::invalid_argument("Invalid mode");
  }
}

void min(std::vector<Shape>& shapes) {
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA") {
    if (shapes.empty()) {
      throw std::invalid_argument("No shapes available");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return getArea(a) < getArea(b);
      });
    std::cout << std::fixed << std::setprecision(1) << getArea(*result) << std::endl;
  } else if (mode == "VERTEXES") {
    if (shapes.empty()) {
      throw std::invalid_argument("No shapes available");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Shape& a, const Shape& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  } else {
    throw std::invalid_argument("Invalid mode");
  }
}

void count(std::vector<Shape>& shapes) {
  std::string mode;
  std::cin >> mode;

  if (mode == "EVEN") {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) {
        return shape.points.size() % 2 == 0;
      }) << std::endl;
  } else if (mode == "ODD") {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) {
        return shape.points.size() % 2 != 0;
      }) << std::endl;
  } else {
    size_t size = std::stoi(mode);
    if (size <= 2) {
      throw std::invalid_argument("Invalid shape size");
    }
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [size](const Shape& shape) {
        return shape.points.size() == size;
      }) << std::endl;
  }
}

void perms(std::vector<Shape>& shapes) {
  Shape local;
  std::cin >> local;
  if (!std::cin) {
    throw std::invalid_argument("Invalid shape input");
  } else {
    std::cout << std::count_if(shapes.begin(), shapes.end(),
      [&local](const Shape& shape) {
        return std::is_permutation(shape.points.begin(), shape.points.end(),
                                   local.points.begin());
      }) << std::endl;
  }
}

