#ifndef FUNCTORS_H
#define FUNCTORS_H

#include "local.h"
#include "geometry.h"

namespace functors
{
    int convertToInt(const std::string& str);
    void getTotalArea(const std::vector<jean::Polygon>& polygons);
    void getMax(const std::vector<jean::Polygon>& polygons);
    void getMin(const std::vector<jean::Polygon>& polygons);
    void getQuantity(const std::vector<jean::Polygon>& polygons);
    void lessArea(std::vector<jean::Polygon>& polygons);
    void same(std::vector<jean::Polygon>& polygons);
    void echo();
    void rightShapes(const std::vector<jean::Polygon>& polygons);
}

#endif

