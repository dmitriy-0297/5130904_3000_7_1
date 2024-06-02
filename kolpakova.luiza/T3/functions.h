#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <vector>

#include "figures.h"

namespace command
{
  int isInputNumber(const std::string& str);
  void area(const std::vector<kolpakova::Polygon>& data);
  void min(const std::vector<kolpakova::Polygon>& data);
  void max(const std::vector<kolpakova::Polygon>& data);
  void count(const std::vector<kolpakova::Polygon>& data);
  void rmecho(std::vector<kolpakova::Polygon>& data);
  void intersections(const std::vector<kolpakova::Polygon>& data);
}

#endif
