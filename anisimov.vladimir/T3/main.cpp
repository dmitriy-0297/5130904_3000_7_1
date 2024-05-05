#include "geometry.h"
#include "commands.h"
#include <iostream>

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "ru");
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " filename\n";
    return 1;
  }

  std::vector<Polygon> polygons = readPolygonsFromFile(argv[1]);

  Polygon comparePolygon;
  comparePolygon.points = { {0, 0}, {2, 2}, {2, 0} };
  commandLessArea(polygons, comparePolygon);

  Polygon targetPolygon;
  targetPolygon.points = { {3, 3}, {1, 1}, {1, 3} };
  commandMaxSeq(polygons, targetPolygon);

  return 0;
}
