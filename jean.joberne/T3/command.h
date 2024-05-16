#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "Polygon.h"

namespace cmd {
    const std::string I_C = "<INVALID COMMAND>";

    int validStringToInt(const std::string &str);
    void area(const std::vector<jean::Polygon> &polygons, const std::string &param);
    void max(const std::vector<jean::Polygon> &polygons, const std::string &param);
    void min(const std::vector<jean::Polygon> &polygons, const std::string &param);
    void count(const std::vector<jean::Polygon> &polygons, const std::string &param);
    void lessArea(const std::vector<jean::Polygon> &polygons);
    void maxSeq(const std::vector<jean::Polygon> &polygons);
}

#endif // COMMAND_H
