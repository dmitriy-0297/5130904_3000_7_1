#include "commands.h"
#include <iostream>
#include <algorithm>

void commandLessArea(const std::vector<Polygon>& polygons, const Polygon& comparePolygon) {
  double compareArea = polygonArea(comparePolygon);
  int count = 0;
  for (const auto& polygon : polygons) {
    if (polygonArea(polygon) < compareArea) {
      count++;
    }
  }
  std::cout << count << std::endl;
}

void commandMaxSeq(const std::vector<Polygon>& polygons, const Polygon& targetPolygon) {
  int maxSeqCount = 0;
  int currSeqCount = 0;
  for (const auto& polygon : polygons) {
    if (polygon.points.size() == targetPolygon.points.size()) {
      bool isEqual = true;
      for (size_t i = 0; i < polygon.points.size(); ++i) {
        if (polygon.points[i].x != targetPolygon.points[i].x || polygon.points[i].y != targetPolygon.points[i].y) {
          isEqual = false;
          break;
        }
      }
      if (isEqual) {
        currSeqCount++;
        maxSeqCount = std::max(maxSeqCount, currSeqCount);
      }
      else {
        currSeqCount = 0;
      }
    }
  }
  std::cout << maxSeqCount << std::endl;
}
