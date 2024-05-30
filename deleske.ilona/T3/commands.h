#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <algorithm>
#include <string>
#include <functional>  // std::bind
#include <numeric>  // std::accumalate
#include <vector>
#include <iostream>

#include "geometry.h"
#include "io.h"

namespace deleske
{
  void area(const std::vector<Polygon> &data);
  void min(const std::vector<Polygon> &data);
  void max(const std::vector<Polygon> &data);
  void count(const std::vector<Polygon> &data);
  void echo(std::vector<Polygon> &data);
  void maxSeq(std::vector<Polygon> &value);
}
#endif
