#include "io.h"
#include <sstream>
#include <regex>

bool jean::isPoint(const std::string &str)
{
    std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
    return std::regex_match(str, pattern);
}

std::ostream &jean::operator<<(std::ostream &out, const jean::Point &point)
{
    return (out << '(' << point.x << ';' << point.y << ')');
}

std::ostream &jean::operator<<(std::ostream &out, const jean::Polygon &polygon)
{
    out << polygon.points.size();
    for (auto &p : polygon.points)
        out << ' ' << p;
    return (out << '\n');
}

std::istream &jean::operator>>(std::istream &in, jean::Point &point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;

    std::string str;
    in >> str;
    if (!jean::isPoint(str))
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    char ch;
    std::stringstream ss(str);
    ss >> ch >> point.x >> ch >> point.y >> ch;
    return in;
}

std::istream &jean::operator>>(std::istream &in, jean::Polygon &polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
        return in;

    polygon.points.clear();
    std::size_t n;
    in >> n;
    if (in.fail() || n < 3)
    {
        in.setstate(std::ios_base::failbit);
        return in;
    }
    polygon.points.resize(n);

    for (auto &p : polygon.points)
    {
        if (in.peek() == '\n')
        {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        in >> p;
    }
    if (in.peek() != '\n')
        in.setstate(std::ios_base::failbit);
    return in;
}

