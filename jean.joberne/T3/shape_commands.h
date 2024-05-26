#ifndef SHAPE_COMMANDS_H
#define SHAPE_COMMANDS_H

#include <functional>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "shape.h"

void perms(std::vector< Shape >& shapes);
void area(std::vector< Shape >& shapes);
void max(std::vector< Shape >& shapes);
void min(std::vector< Shape >& shapes);
void count(std::vector< Shape >& shapes);

#endif
