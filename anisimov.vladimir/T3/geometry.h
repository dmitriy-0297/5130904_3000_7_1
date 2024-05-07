#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <string>

struct Point {
  int x, y;
};
struct Polygon {
  std::vector<Point> points;
};

double polygonArea(const Polygon& polygon);
std::vector<Polygon> readPolygonsFromFile(const std::string& filename);
#endif
