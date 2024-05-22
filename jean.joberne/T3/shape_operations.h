#ifndef SHAPE_OPERATIONS_H
#define SHAPE_OPERATIONS_H

#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "shapes.h"

void perms(std::vector<Shape>& shapes);
void area(std::vector<Shape>& shapes);
void max(std::vector<Shape>& shapes);
void min(std::vector<Shape>& shapes);
void count(std::vector<Shape>& shapes);

#endif // SHAPE_OPERATIONS_H

