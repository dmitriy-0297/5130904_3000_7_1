#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include "geometry.h"

namespace jean
{
    std::istream& operator>>(std::istream& in, Point& point);
    std::istream& operator>>(std::istream& in, Polygon& polygon);
    std::ostream& operator<<(std::ostream& out, const Point& point);
    std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
    bool isPoint(const std::string& str);
}

#endif

