#ifndef METHODS_H
#define METHODS_H

#include "local.h"
#include "geometry.h"

namespace anisimov {
  namespace methods {
    int convertToInt(const std::string& str);
    void getTotalArea(const std::vector<Polygon>& polygons);
    void getMax(const std::vector<Polygon>& polygons);
    void getMin(const std::vector<Polygon>& polygons);
    void getQuantity(const std::vector<Polygon>& polygons);
    void lessArea(std::vector<Polygon>& polygons);
    void maxseq(std::vector<Polygon>& polygons);
  }
}
#endif
