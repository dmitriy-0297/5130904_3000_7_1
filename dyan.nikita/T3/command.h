#ifndef COMMAND_H
#define COMMAND_H

#include "local.h"
#include "shape.h"

namespace command
{
  int is_a_num(const std::string& str);
  void area(const std::vector<dyan::Polygon>& data, const std::string& arg);
  void max(const std::vector<dyan::Polygon>& data, const std::string& arg);
  void min(const std::vector<dyan::Polygon>& data, const std::string& arg);
  void count(const std::vector<dyan::Polygon>& data, const std::string& arg);
  void rmecho(std::vector<dyan::Polygon>& data);
  void same(const std::vector<dyan::Polygon>& data, dyan::Polygon& target);
}

#endif
