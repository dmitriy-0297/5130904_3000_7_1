#include "functors.h"
#include "geometry.h"
#include "io.h"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <numeric>
#include <functional>
#include <vector>
#include <string>
#include <cmath>

using namespace jean;
using namespace std::placeholders;

// Function to get the total area of polygons based on criteria
void functors::getTotalArea(const std::vector<jean::Polygon>& data)
{
    auto accumulateAreaIf = [](double ac, const jean::Polygon& poly, std::size_t mod2, std::size_t vertices)
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
                    std::bind(accumulateAreaIf, _1, _2, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                    std::bind(accumulateAreaIf, _1, _2, 1, 0)) << '\n';
    }
    else if (arg == "MEAN" && data.size() != 0)
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                     std::bind(accumulateAreaIf, _1, _2, 3, 0)) / data.size() << std::endl;
    }
    else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
    {
        std::cout << std::accumulate(data.begin(), data.end(), 0.0,
                    std::bind(accumulateAreaIf, _1, _2, 2, stoi(arg))) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

// Function to get the minimum area or vertex count of polygons
void functors::getMin(const std::vector<jean::Polygon>& data)
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
        std::cout << std::min_element(data.begin(), data.end(), 
            [](const jean::Polygon& a, const jean::Polygon& b)
            {
                return a.points.size() < b.points.size();
            })->points.size() << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

// Function to get the maximum area or vertex count of polygons
void functors::getMax(const std::vector<jean::Polygon>& data)
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
        std::cout << std::max_element(data.begin(), data.end(),
            [](const jean::Polygon& a, const jean::Polygon& b)
            {
                return a.points.size() < b.points.size();
            })->points.size() << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

// Function to count polygons based on criteria
void functors::getQuantity(const std::vector<jean::Polygon>& data)
{
    auto countPolygonsIf = [](const jean::Polygon& poly, std::size_t mod2, std::size_t vertices)
    {
        return ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices));
    };

    std::string arg;
    std::cin >> arg;
    if (arg == "EVEN")
    {
        std::cout << std::count_if(data.begin(), data.end(),
                    std::bind(countPolygonsIf, _1, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
        std::cout << std::count_if(data.begin(), data.end(),
                    std::bind(countPolygonsIf, _1, 1, 0)) << '\n';
    }
    else if (std::all_of(arg.begin(), arg.end(), isdigit) && stoi(arg) > 2)
    {
        std::cout << std::count_if(data.begin(), data.end(),
                    std::bind(countPolygonsIf, _1, 2, stoi(arg))) << '\n';
    }
    else
    {
        throw std::runtime_error("<INVALID COMMAND>");
    }
}

// Function to count polygons with area less than a given polygon
void functors::lessArea(const std::vector<jean::Polygon>& data)
{
    jean::Polygon basic;
    std::cin >> basic;
    if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

    std::cout << std::count_if(data.begin(), data.end(),
        [&basic](const jean::Polygon& poly)
        {
            return poly.getArea() < basic.getArea();
        }) << '\n';
}

// Function to count polygons that are identical to a given polygon
void functors::same(const std::vector<jean::Polygon>& data)
{
    jean::Polygon basic;
    std::cin >> basic;
    if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

    std::cout << std::count(data.begin(), data.end(), basic) << '\n';
}

// Function to duplicate occurrences of a given polygon
void functors::echo(std::vector<jean::Polygon>& data)
{
    jean::Polygon poly;
    std::cin >> poly;
    if (std::cin.fail() || std::cin.get() != '\n')
        throw std::runtime_error("<INVALID COMMAND>");

    std::vector<jean::Polygon> result;
    int count = 0;
    for (const jean::Polygon& el : data)
    {
        result.push_back(el);
        if (el == poly)
        {
            ++count;
            result.push_back(el);
        }
    }
    data.swap(result);
    std::cout << count << '\n';
}

