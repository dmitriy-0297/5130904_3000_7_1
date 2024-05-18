#include "functors.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>
#include <iterator>
#include <stdexcept>

using namespace std::placeholders;

void jean::area(const std::vector<Polygon> &data)
{
    auto accumulateArea_if = [](double ac, const jean::Polygon &poly, std::size_t mod2, std::size_t vertices)
    {
        if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3))
        {
            ac += poly.getArea();
        }
        return ac;
    };

    std::string arg;
    std::cin >> arg;
    if (arg == "EVEN")
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                     std::bind(accumulateArea_if, _1, _2, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                     std::bind(accumulateArea_if, _1, _2, 1, 0)) << '\n';
    }
    else if (arg == "MEAN" && data.size() != 0)
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                     std::bind(accumulateArea_if, _1, _2, 3, 0)) / data.size() << std::endl;
    }
    else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                                     std::bind(accumulateArea_if, _1, _2, 2, stoi(arg))) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

void jean::min(const std::vector<Polygon> &data)
{
    if (data.empty())
        throw std::runtime_error("<INVALID COMMAND>");

    std::string arg;
    std::cin >> arg;

    if (arg == "AREA")
    {
        std::cout << std::min_element(data.begin(), data.end())->getArea() << '\n';
    }
    else if (arg == "VERTEXES")
    {
        std::vector<std::size_t> sizes(data.size());

        std::cout << std::accumulate(
                         data.begin() + 1,
                         data.end(),
                         data[0].points.size(),
                         [](std::size_t min, const Polygon &poly)
                         {
                             return (poly.points.size() < min ? poly.points.size() : min);
                         }) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

void jean::max(const std::vector<Polygon> &data)
{
    if (data.empty())
        throw std::runtime_error("<INVALID COMMAND>");

    std::string arg;
    std::cin >> arg;

    if (arg == "AREA")
    {
        std::cout << std::max_element(data.begin(), data.end())->getArea() << '\n';
    }
    else if (arg == "VERTEXES")
    {
        std::vector<std::size_t> sizes(data.size());

        std::cout << std::accumulate(
                         data.begin() + 1,
                         data.end(),
                         data[0].points.size(),
                         [](std::size_t max, const Polygon &poly)
                         {
                             return (poly.points.size() > max ? poly.points.size() : max);
                         }) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

void jean::count(const std::vector<Polygon> &data)
{
    auto countPolygons_if = [](const jean::Polygon &poly, std::size_t mod2, std::size_t vertices)
    {
        return ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices));
    };

    std::string arg;
    std::cin >> arg;
    if (arg == "EVEN")
    {
        std::cout << std::count_if(data.begin(), data.end(),
                                   std::bind(countPolygons_if, _1, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
        std::cout << std::count_if(data.begin(), data.end(),
                                   std::bind(countPolygons_if, _1, 1, 0)) << '\n';
    }
    else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
    {
        std::cout << std::count_if(data.begin(), data.end(),
                                   std::bind(countPolygons_if, _1, 2, stoi(arg))) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

void jean::echo(std::vector<Polygon> &data)
{
    jean::Polygon poly;
    std::cin >> poly;
    if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

    std::vector<Polygon> result;
    int count = 0;
    for (const Polygon &el : data)
    {
        result.push_back(el);
        if (el == poly)
        {
            ++count;
            result.push_back(el);
        }
    }
    data.resize(result.size());
    copy(result.begin(), result.end(), data.begin());
    std::cout << count << '\n';
}

void jean::inframe(const std::vector<Polygon> &data)
{
    jean::Polygon poly;
    std::cin >> poly;
    if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

    jean::Frame frame = getFrame(data);
    std::cout << (frame.containsPolygon(poly) ? "<TRUE>" : "<FALSE>") << '\n';
}

