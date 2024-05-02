#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <limits>
#include <cmath>

struct Point
{
    int x, y;
};
std::istream& operator>>(std::istream& in, Point& p)
{
    char ch1, ch2, ch3;
    if (in >> ch1 >> p.x >> ch2 >> p.y >> ch3 && ch1 == '(' && ch2 == ';' && ch3 == ')')
        return in;
    in.setstate(std::ios_base::failbit);
    return in;
}
struct Polygon
{
    std::vector<Point> points;
    double area() const
    {
        double result = 0.0;
        for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++)
        {
            result += (points[j].x + points[i].x) * (points[j].y - points[i].y);
        }
        return std::abs(result / 2.0);
    }
};
std::istream& operator>>(std::istream& in, Polygon& poly)
{
    int count;
    if (!(in >> count))
    {
        return in;
    }
    poly.points.clear();
    Point temp;
    for (int i = 0; i < count; ++i)
    {
        if (in >> temp)
        {
            poly.points.push_back(temp);
        }
        else {
            in.setstate(std::ios_base::failbit);
            return in;
        }
    }
    return in;
}
void executeArea(const std::vector<Polygon>& polygons, const std::string& param)
{
    double result = 0.0;
    if (param == "EVEN")
    {
        result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p)
            {
                return acc + (p.points.size() % 2 == 0 ? p.area() : 0);
            });
    }
    else if (param == "ODD")
    {
        result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
            [](double acc, const Polygon& p)
            {
                return acc + (p.points.size() % 2 != 0 ? p.area() : 0);
            });
    }
    else if (param == "MEAN")
    {
        if (!polygons.empty())
        {
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p)
                {
                    return acc + p.area();
                }) / polygons.size();
        }
    }
    else
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(1) << result << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return EXIT_FAILURE;
    }
    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Error: file didn't open\n";
        return EXIT_FAILURE;
    }
    std::vector<Polygon> polygons;
    Polygon poly;
    while (file >> poly)
    {
        polygons.push_back(poly);
    }
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string command, param;
        iss >> command >> param;
        if (command == "AREA")
        {
            executeArea(polygons, param);
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    return 0;
}
