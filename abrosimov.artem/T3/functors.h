#ifndef FUNCTORS_H
#define FUNCTORS_H

#include "local.h"
#include "geometry.h"

namespace functors
{
    int convertToInt(const std::string& str);
    void getTotalArea(const std::vector<abrosimov::Polygon>& polygons);
    void getMax(const std::vector<abrosimov::Polygon>& polygons);
    void getMin(const std::vector<abrosimov::Polygon>& polygons);
    void getQuantity(const std::vector<abrosimov::Polygon>& polygons);
    void lessArea(std::vector<abrosimov::Polygon>& polygons);
    void same(std::vector<abrosimov::Polygon>& polygons);
}

#endif
