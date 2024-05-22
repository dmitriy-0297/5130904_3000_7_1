#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Polygon.h"

void area(const std::vector<Polygon>& polygons);
void perms(const std::vector<Polygon>& polygons);
void count(const std::vector<Polygon>& polygons);
void max(const std::vector<Polygon>& polygons);
void min(const std::vector<Polygon>& polygons);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  std::ifstream inputF(argv[1]);
  if (!inputF) {
    return 1;
  }

  std::vector<Polygon> polygons;
  while (inputF) {
    Polygon polygon;
    inputF >> polygon;
    if (inputF) {
      polygons.push_back(polygon);
    }
    if (inputF.fail() && !inputF.eof()) {
      inputF.clear();
      inputF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::string command;
  while (std::cin >> command) {
    try {
      if (command == "AREA") {
        area(polygons);
      } else if (command == "PERMS") {
        perms(polygons);
      } else if (command == "COUNT") {
        count(polygons);
      } else if (command == "MAX") {
        max(polygons);
      } else if (command == "MIN") {
        min(polygons);
      } else {
        throw std::invalid_argument("Invalid command");
      }
    } catch (...) {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }

  return 0;
}

void area(const std::vector<Polygon>& polygons) {
  std::string mode;
  std::cin >> mode;
  std::cout << std::fixed << std::setprecision(1);

  if (mode == "EVEN") {
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon) {
        if (polygon.points.size() % 2 == 0) {
          double polygonArea = std::abs(std::accumulate(
            polygon.points.begin(), polygon.points.end(), 0.0,
            [](double acc, const Point& point) {
              return acc + (point.x * point.y);
            }
          ));
          return area + polygonArea;
        }
        return area;
      });
    std::cout << totalArea << '\n';
  } else if (mode == "ODD") {
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon) {
        if (polygon.points.size() % 2 != 0) {
          double polygonArea = std::abs(std::accumulate(
            polygon.points.begin(), polygon.points.end(), 0.0,
            [](double acc, const Point& point) {
              return acc + (point.x * point.y);
            }
          ));
          return area + polygonArea;
        }
        return area;
      });
    std::cout << totalArea << '\n';
  } else if (mode == "MEAN") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon) {
        double polygonArea = std::abs(std::accumulate(
          polygon.points.begin(), polygon.points.end(), 0.0,
          [](double acc, const Point& point) {
            return acc + (point.x * point.y);
          }
        ));
        return area + polygonArea;
      });
    double meanArea = totalArea / polygons.size();
    std::cout << meanArea << '\n';
  } else {
    size_t size = std::stoull(mode);
    if (size <= 2) {
      throw std::invalid_argument("Invalid polygon size");
    }
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [size](double area, const Polygon& polygon) {
        if (polygon.points.size() == size) {
          double polygonArea = std::abs(std::accumulate(
            polygon.points.begin(), polygon.points.end(), 0.0,
            [](double acc, const Point& point) {
              return acc + (point.x * point.y);
            }
          ));
          return area + polygonArea;
        }
        return area;
      });
    std::cout << totalArea << '\n';
  }
}

void perms(const std::vector<Polygon>& polygons) {
  Polygon local;
  std::cin >> local;
  if (!std::cin) {
    throw std::invalid_argument("Invalid polygon input");
  } else {
    int count = std::count_if(polygons.begin(), polygons.end(),
      [&local](const Polygon& polygon) {
        return std::is_permutation(polygon.points.begin(),
                                   polygon.points.end(),
                                   local.points.begin());
      });
    std::cout << count << '\n';
  }
}

void count(const std::vector<Polygon>& polygons) {
  std::string mode;
  std::cin >> mode;

  if (mode == "EVEN") {
    int count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& polygon) {
        return polygon.points.size() % 2 == 0;
      });
    std::cout << count << '\n';
  } else if (mode == "ODD") {
    int count = std::count_if(polygons.begin(), polygons.end(),
      [](const Polygon& polygon) {
        return polygon.points.size() % 2 != 0;
      });
    std::cout << count << '\n';
  } else {
    size_t size = std::stoi(mode);
    if (size <= 2) {
      throw std::invalid_argument("Invalid polygon size");
    }
    int count = std::count_if(polygons.begin(), polygons.end(),
      [size](const Polygon& polygon) {
        return polygon.points.size() == size;
      });
    std::cout << count << '\n';
  }
}

void max(const std::vector<Polygon>& polygons) {
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    auto maxPolygon = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        double areaA = std::abs(std::accumulate(a.points.begin(), a.points.end(), 0.0,
          [](double acc, const Point& point) {
            return acc + (point.x * point.y);
          }
        ));
        double areaB = std::abs(std::accumulate(b.points.begin(), b.points.end(), 0.0,
          [](double acc, const Point& point) {
            return acc + (point.x * point.y);
          }
        ));
        return areaA < areaB;
      });
    double maxArea = std::abs(std::accumulate(maxPolygon->points.begin(), maxPolygon->points.end(), 0.0,
      [](double acc, const Point& point) {
        return acc + (point.x * point.y);
      }
    ));
    std::cout << maxArea << '\n';
  } else if (mode == "VERTEXES") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    auto maxPolygon = std::max_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << maxPolygon->points.size() << '\n';
  } else {
    throw std::invalid_argument("Invalid mode");
  }
}

void min(const std::vector<Polygon>& polygons) {
  std::string mode;
  std::cin >> mode;

  if (mode == "AREA") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    auto minPolygon = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        double areaA = std::abs(std::accumulate(a.points.begin(), a.points.end(), 0.0,
          [](double acc, const Point& point) {
            return acc + (point.x * point.y);
          }
        ));
        double areaB = std::abs(std::accumulate(b.points.begin(), b.points.end(), 0.0,
          [](double acc, const Point& point) {
            return acc + (point.x * point.y);
          }
        ));
        return areaA < areaB;
      });
    double minArea = std::abs(std::accumulate(minPolygon->points.begin(), minPolygon->points.end(), 0.0,
      [](double acc, const Point& point) {
        return acc + (point.x * point.y);
      }
    ));
    std::cout << minArea << '\n';
  } else if (mode == "VERTEXES") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    auto minPolygon = std::min_element(polygons.begin(), polygons.end(),
      [](const Polygon& a, const Polygon& b) {
        return a.points.size() < b.points.size();
      });
    std::cout << minPolygon->points.size() << '\n';
  } else {
    throw std::invalid_argument("Invalid mode");
  }
}

