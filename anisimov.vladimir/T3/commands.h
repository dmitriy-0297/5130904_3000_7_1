#ifndef COMMANDS_H
#define COMMANDS_H
#include "geometry.h"
void commandLessArea(const std::vector<Polygon>& polygons, const Polygon& comparePolygon);
void commandMaxSeq(const std::vector<Polygon>& polygons, const Polygon& targetPolygon);
#endif
