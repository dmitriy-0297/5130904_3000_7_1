#ifndef COMMANDS_H
#define COMMANDS_H
#include "utils.h"
#include "geometry.h"

namespace cmd
{
    void area(std::vector<geometry::Polygon>& value, const std::string& str);
    void max(std::vector<geometry::Polygon>& value, const std::string& str);
    void min(std::vector<geometry::Polygon>& value, const std::string& str);
    void count(std::vector<geometry::Polygon>& value, const std::string& str);
    void lessArea(std::vector<geometry::Polygon>& value);
    void maxSeq(std::vector<geometry::Polygon>& value);
    void echo(std::vector<geometry::Polygon>& value);
    void inFrame(std::vector<geometry::Polygon>& value);
}

#endif
