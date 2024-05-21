#ifndef POLYGON_COMMANDS_H
#define POLYGON_COMMANDS_H

#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "Polygon.h"

void perms(std::vector< Polygon >& polygons);

void rightShapes(std::vector< Polygon >& polygons);

void area(std::vector< Polygon >& polygons);

void max(std::vector< Polygon >& polygons);

void min(std::vector< Polygon >& polygons);

void count(std::vector< Polygon >& polygons);

#endif
