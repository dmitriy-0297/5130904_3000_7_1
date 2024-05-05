#include "geometry.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>

double polygonArea(const Polygon& polygon) {
  double area = 0.0;
  int n = polygon.points.size();
  for (int i = 0; i < n; ++i) {
    int j = (i + 1) % n;
    area += polygon.points[i].x * polygon.points[j].y;
    area -= polygon.points[j].x * polygon.points[i].y;
  }
  area = std::abs(area) / 2.0;
  return area;
}

std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
  std::ifstream file(filename);
  std::vector<Polygon> polygons;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    int numVertices;
    if (iss >> numVertices) {
      Polygon polygon;
      for (int i = 0; i < numVertices; ++i) {
        char delimiter;
        Point point;
        if (iss >> delimiter >> point.x >> delimiter >> point.y >> delimiter) {
          polygon.points.push_back(point);
        }
        else {
          break;
        }
      }
      if (polygon.points.size() == numVertices) {
        polygons.push_back(polygon);
      }
    }
  }
  return polygons;
}
