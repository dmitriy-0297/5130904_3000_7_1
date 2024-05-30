#ifndef SHAPE_COMMANDS_H
#define SHAPE_COMMANDS_H

#include <vector>
#include "shape.h"

void perms(const std::vector<Polygon>& shapes);
void area(const std::vector<Polygon>& shapes);
void max(const std::vector<Polygon>& shapes);
void min(const std::vector<Polygon>& shapes);
void count(const std::vector<Polygon>& shapes);

#endif // SHAPE_COMMANDS_H
