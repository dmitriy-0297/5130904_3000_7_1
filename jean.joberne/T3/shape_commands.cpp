#include "shape_commands.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <iomanip> // Добавлено для использования std::setprecision

using namespace std::placeholders;

void perms(const std::vector<Polygon>& shapes) {
  Polygon local;
  std::cin >> local;
  if (!std::cin) {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  auto count = std::count_if(shapes.begin(), shapes.end(),
                             [&local](const Polygon& shape) {
                               return std::is_permutation(shape.points.begin(),
                                                         shape.points.end(),
                                                         local.points.begin());
                             });
  std::cout << count << std::endl;
}

void area(const std::vector<Polygon>& shapes) {
  std::string mode;
  std::cin >> mode;
  std::cout << std::fixed << std::setprecision(1);
  if (mode == "EVEN") {
    double result = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double sum, const Polygon& shape) {
        return sum + ((shape.points.size() % 2 == 0) ? getArea(shape) : 0.0);
      });
    std::cout << result << std::endl;
  } else if (mode == "ODD") {
    double result = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double sum, const Polygon& shape) {
        return sum + ((shape.points.size() % 2 != 0) ? getArea(shape) : 0.0);
      });
    std::cout << result << std::endl;
  } else if (mode == "MEAN") {
    if (shapes.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    double result = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [](double sum, const Polygon& shape) {
        return sum + getArea(shape);
      }) / shapes.size();
    std::cout << result << std::endl;
  } else {
    size_t size = std::stoull(mode);
    if (size <= 2) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    double result = std::accumulate(shapes.begin(), shapes.end(), 0.0,
      [size](double sum, const Polygon& shape) {
        return sum + ((shape.points.size() == size) ? getArea(shape) : 0.0);
      });
    std::cout << result << std::endl;
  }
}

void max(const std::vector<Polygon>& shapes) {
  std::string mode;
  std::cin >> mode;
  if (mode == "AREA") {
    if (shapes.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
      });
    std::cout << std::fixed << std::setprecision(1);
    std::cout << getArea(*result) << std::endl;
  } else if (mode == "VERTEXES") {
    if (shapes.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::max_element(shapes.begin(), shapes.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  } else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void min(const std::vector<Polygon>& shapes) {
  std::string mode;
  std::cin >> mode;
  if (mode == "AREA") {
    if (shapes.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Polygon& a, const Polygon& b) {
        return getArea(a) < getArea(b);
      });
    std::cout << std::fixed << std::setprecision(1);
    std::cout << getArea(*result) << std::endl;
  } else if (mode == "VERTEXES") {
    if (shapes.empty()) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::min_element(shapes.begin(), shapes.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << result->points.size() << std::endl;
  } else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void count(const std::vector<Polygon>& shapes) {
  std::string mode;
  std::cin >> mode;
  if (mode == "EVEN") {
    auto result = std::count_if(shapes.begin(), shapes.end(),
      [](const Polygon& shape) {
        return shape.points.size() % 2 == 0;
      });
    std::cout << result << std::endl;
  } else if (mode == "ODD") {
    auto result = std::count_if(shapes.begin(), shapes.end(),
      [](const Polygon& shape) {
        return shape.points.size() % 2 != 0;
      });
    std::cout << result << std::endl;
  } else {
    size_t size = std::stoull(mode);
    if (size <= 2) {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    auto result = std::count_if(shapes.begin(), shapes.end(),
      [size](const Polygon& shape) {
        return shape.points.size() == size;
      });
    std::cout << result << std::endl;
  }
}
