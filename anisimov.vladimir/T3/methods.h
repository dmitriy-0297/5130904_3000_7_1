#ifndef METHODS_H
#define METHODS_H

#include "local.h"
#include "geometry.h"

namespace methods
{
  int convertToInt(const std::string& str);
  void getTotalArea(const std::vector<anisimov::Polygon>& polygons);
  void getMax(const std::vector<anisimov::Polygon>& polygons);
  void getMin(const std::vector<anisimov::Polygon>& polygons);
  void getQuantity(const std::vector<anisimov::Polygon>& polygons);
  void lessArea(std::vector<anisimov::Polygon>& polygons);
  void maxseq(std::vector<anisimov::Polygon>& polygons);
}

#endif
