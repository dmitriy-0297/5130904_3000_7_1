#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "Polygon.h"

namespace cmd {
    int validStringToInt(const std::string &str);
    void area(const std::vector<jean::Polygon> &value, const std::string &str);
    void max(const std::vector<jean::Polygon> &value, const std::string &str);
    void min(const std::vector<jean::Polygon> &value, const std::string &str);
    void count(const std::vector<jean::Polygon> &value, const std::string &str);
    void lessArea(const std::vector<jean::Polygon> &value);
    void maxSeq(const std::vector<jean::Polygon> &value);
}

#endif // COMMAND_H

