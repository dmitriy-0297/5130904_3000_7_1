#ifndef COMMAND_H
#define COMMAND_H

#include "local.h"
#include "figure.h"

namespace commands
{
  int convertToNumber(const std::string& str);
  void getFullArea(const std::vector<golikov::Polygon>& polygons);
  void getMin(const std::vector<golikov::Polygon>& data);
  void getMax(const std::vector<golikov::Polygon>& data);
  void countFigures(const std::vector<golikov::Polygon>& polygons);
  golikov::FrameRectangle getFrameRectangle(const std::vector<golikov::Polygon>& polygons);
  void checkStream();
  void lessarea(std::vector<golikov::Polygon>& value);
  void intersections(const std::vector<golikov::Polygon>& data);
}

#endif
