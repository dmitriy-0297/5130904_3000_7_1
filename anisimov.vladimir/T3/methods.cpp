#include "methods.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <functional>

using namespace std::placeholders;

namespace anisimov {
  namespace methods {

    void area(const std::vector<Polygon>& polygons) {
      auto accumulateArea_if = [](double ac, const Polygon& poly, std::size_t mod2, std::size_t vertices) {
        if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3)) {
          ac += poly.getArea();
        }
        return ac;
        };

      std::string arg;
      std::cin >> arg;
      if (arg == "EVEN") {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(accumulateArea_if, _1, _2, 0, 0)) << '\n';
      }
      else if (arg == "ODD") {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(accumulateArea_if, _1, _2, 1, 0)) << '\n';
      }
      else if (arg == "MEAN" && !polygons.empty()) {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(accumulateArea_if, _1, _2, 3, 0)) / polygons.size() << std::endl;
      }
      else if (std::all_of(arg.begin(), arg.end(), isdigit) && std::stoi(arg) > 2) {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0, std::bind(accumulateArea_if, _1, _2, 2, std::stoi(arg))) << '\n';
      }
      else {
        throw std::runtime_error("<INVALID COMMAND>");
      }
    }

    void min(const std::vector<Polygon>& polygons) {
      if (polygons.empty())
        throw std::runtime_error("<INVALID COMMAND>");

      std::string arg;
      std::cin >> arg;

      if (arg == "AREA") {
        std::cout << std::min_element(polygons.begin(), polygons.end())->getArea() << '\n';
      }
      else if (arg == "VERTEXES") {
        std::cout << std::accumulate(
          polygons.begin() + 1,
          polygons.end(),
          polygons[0].points.size(),
          [](std::size_t min, const Polygon& poly) {
            return (poly.points.size() < min ? poly.points.size() : min);
          }
        ) << '\n';
      }
      else {
        throw std::runtime_error("<INVALID COMMAND>");
      }
    }

    void max(const std::vector<Polygon>& polygons) {
      if (polygons.empty())
        throw std::runtime_error("<INVALID COMMAND>");

      std::string arg;
      std::cin >> arg;

      if (arg == "AREA") {
        std::cout << std::max_element(polygons.begin(), polygons.end())->getArea() << '\n';
      }
      else if (arg == "VERTEXES") {
        std::cout << std::accumulate(
          polygons.begin() + 1,
          polygons.end(),
          polygons[0].points.size(),
          [](std::size_t max, const Polygon& poly) {
            return (poly.points.size() > max ? poly.points.size() : max);
          }
        ) << '\n';
      }
      else {
        throw std::runtime_error("<INVALID COMMAND>");
      }
    }

    void count(const std::vector<Polygon>& polygons) {
      auto countPolygons_if = [](const Polygon& poly, std::size_t mod2, std::size_t vertices) {
        return ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices));
        };

      std::string arg;
      std::cin >> arg;
      if (arg == "EVEN") {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(countPolygons_if, _1, 0, 0)) << '\n';
      }
      else if (arg == "ODD") {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(countPolygons_if, _1, 1, 0)) << '\n';
      }
      else if (std::all_of(arg.begin(), arg.end(), isdigit) && std::stoi(arg) > 2) {
        std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(countPolygons_if, _1, 2, std::stoi(arg))) << '\n';
      }
      else {
        throw std::runtime_error("<INVALID COMMAND>");
      }
    }

    void echo(std::vector<Polygon>& polygons) {
      if (polygons.empty()) {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      Polygon poly;
      std::cin >> poly;
      if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

      std::vector<Polygon> result;
      int count = 0;
      for (const Polygon& el : polygons) {
        result.push_back(el);
        if (el == poly) {
          ++count;
          result.push_back(el);
        }
      }
      polygons.resize(result.size());
      std::copy(result.begin(), result.end(), polygons.begin());
      std::cout << count << '\n';
    }

    void maxseq(std::vector<Polygon>& polygons) {
      if (polygons.empty()) {
        throw std::runtime_error("<INVALID COMMAND>");
      }
      Polygon poly;
      std::cin >> poly;
      if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

      int maxCount = 0;
      int currentCount = 0;

      auto counter = [&](const Polygon& tPolygon) {
        if (poly == tPolygon) {
          currentCount++;
        }
        else {
          maxCount = std::max(maxCount, currentCount);
          currentCount = 0;
        }
        return false;
        };
      currentCount = std::count_if(polygons.begin(), polygons.end(), counter);
      maxCount = std::max(maxCount, currentCount);
      std::cout << maxCount << "\n";
    }
  }
}
