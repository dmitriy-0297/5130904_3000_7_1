#ifndef COMMAND_H
#define COMMAND_H

#include "local.h"
#include "shape.h"

namespace command
{
  int convertToNumber(const std::string& str);
  void getTotalArea(const std::vector<gubanov::Polygon>& polygons);
  void calculateMinOrMax(const std::vector<gubanov::Polygon>& polygons, const std::string& method);
  void countPolygons(const std::vector<gubanov::Polygon>& polygons);
  gubanov::FrameRectangle getFrameRectangle(const std::vector<gubanov::Polygon>& polygons);
  void checkStream();
  void InFrame(const std::vector<gubanov::Polygon>& polygons);
  void echo(std::vector<gubanov::Polygon>& polygons);
}

#endif
