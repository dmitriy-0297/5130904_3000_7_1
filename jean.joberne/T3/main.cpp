#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <iomanip>
#include "Polygon.h"

void area(const std::vector<Polygon>& polygons);
void perms(const std::vector<Polygon>& polygons);

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
        return polygon.points.size() % 2 == 0
            ? area + std::abs(std::accumulate(
                polygon.points.begin(), polygon.points.end(), 0.0,
                [](double acc, const Point& point) {
                  return acc + (point.x * point.y);
                }))
            : area;
      });
    std::cout << totalArea << '\n';
  } else if (mode == "ODD") {
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon) {
        return polygon.points.size() % 2 != 0
            ? area + std::abs(std::accumulate(
                polygon.points.begin(), polygon.points.end(), 0.0,
                [](double acc, const Point& point) {
                  return acc + (point.x * point.y);
                }))
            : area;
      });
    std::cout << totalArea << '\n';
  } else if (mode == "MEAN") {
    if (polygons.empty()) {
      throw std::invalid_argument("No polygons available");
    }
    double meanArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [](double area, const Polygon& polygon) {
        return area + std::abs(std::accumulate(
            polygon.points.begin(), polygon.points.end(), 0.0,
            [](double acc, const Point& point) {
              return acc + (point.x * point.y);
            }));
      }) / polygons.size();
    std::cout << meanArea << '\n';
  } else {
    size_t size = std::stoull(mode);
    if (size <= 2) {
      throw std::invalid_argument("Invalid polygon size");
    }
    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
      [size](double area, const Polygon& polygon) {
        return polygon.points.size() == size
            ? area + std::abs(std::accumulate(
                polygon.points.begin(), polygon.points.end(), 0.0,
                [](double acc, const Point& point) {
                  return acc + (point.x * point.y);
                }))
            : area;
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

