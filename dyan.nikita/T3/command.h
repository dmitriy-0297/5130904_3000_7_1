#ifndef COMMAND_H
#define COMMAND_H

#include "local.h"
#include "shape.h"

namespace command
{
  int is_a_num(const std::string& str);
  void area(const std::vector<dyan::Polygon>& data);
  void max(const std::vector<dyan::Polygon>& data);
  void min(const std::vector<dyan::Polygon>& data);
  void count(const std::vector<dyan::Polygon>& data);
  void rmecho(std::vector<dyan::Polygon>& data);
  void same(std::vector<dyan::Polygon>& data);
}

#endif
