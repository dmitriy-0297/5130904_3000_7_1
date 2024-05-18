#include "functors.h"

using namespace jean;
using namespace std::placeholders;

int functors::convertToInt(const std::string& str)
{
    try
    {
        return std::stoi(str);
    }
    catch (const std::invalid_argument&)
    {
        return -1;
    }
    catch (const std::out_of_range&)
    {
        return -1;
    }
}

void functors::getTotalArea(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;
    int number = convertToInt(string);
    auto accumulateArea = [&polygons, &number]
    (double accumulatedArea, const Polygon& current, const std::string method)
        {
            double result = accumulatedArea;
            if (method == "EVEN" and current.points.size() % 2 == 0)
            {
                result += current.getArea();
            }
            else if (method == "ODD" and current.points.size() % 2 != 0)
            {
                result += current.getArea();
            }
            else if (method == "MEAN")
            {
                result += current.getArea();
            }
            else if (method == "SPECIAL" and current.points.size() == static_cast<size_t>(number))
            {
                result += current.getArea();
            }
            return result;
        };

    if (number == -1)
    {
        if (string == "EVEN" or string == "ODD")
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(accumulateArea, _1, _2, string)) << std::endl;
        }
        else if (string == "MEAN" and polygons.size() != 0)
        {
            std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                std::bind(accumulateArea, _1, _2, string)) / polygons.size() << std::endl;
        }
        else
        {
            throw "<INVALID COMMAND>";
        }
    }
    else if (number > 2)
    {
        std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
            std::bind(accumulateArea, _1, _2, "SPECIAL")) << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void functors::getMax(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;

    if (polygons.size() == 0)
    {
        throw "<INVALID COMMAND>";
    }

    std::vector<size_t> vectorSize(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vectorSize.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });
    auto polygon = std::max_element(polygons.begin(), polygons.end());
    auto maxSize = std::max_element(vectorSize.begin(), vectorSize.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *maxSize << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void functors::getMin(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;

    if (polygons.size() == 0)
    {
        throw "<INVALID COMMAND>";
    }

    std::vector<size_t> vectorSize(polygons.size());

    std::transform(polygons.begin(), polygons.end(), vectorSize.begin(),
        [](const Polygon& poly)
        {
            return poly.points.size();
        });

    auto polygon = std::min_element(polygons.begin(), polygons.end());
    auto minSize = std::min_element(vectorSize.begin(), vectorSize.end());

    if (string == "AREA")
    {
        std::cout << polygon->getArea() << std::endl;
    }
    else if (string == "VERTEXES")
    {
        std::cout << *minSize << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void functors::getQuantity(const std::vector<Polygon>& polygons)
{
    std::string string;
    std::cin >> string;
    int number = convertToInt(string);
    auto count = [&number](const Polygon& polygon, const std::string& method)
        {
            if (method == "EVEN")
            {
                return polygon.points.size() % 2 == 0;
            }
            else if (method == "ODD")
            {
                return polygon.points.size() % 2 != 0;
            }
            else if (method == "SPECIAL")
            {
                return polygon.points.size() == static_cast<size_t>(number);
            }
            return false;
        };

    if (number == -1)
    {
        if (string == "EVEN" or string == "ODD")
        {
            std::cout << std::count_if(polygons.begin(), polygons.end(),
                std::bind(count, _1, string)) << std::endl;
        }
        else
        {
            throw "<INVALID COMMAND>";
        }
    }
    else if (number > 2)
    {
        std::cout << std::count_if(polygons.begin(), polygons.end(),
            std::bind(count, _1, "SPECIAL")) << std::endl;
    }
    else
    {
        throw "<INVALID COMMAND>";
    }
}

void functors::lessArea(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw "<INVALID COMMAND>";
    }

    Polygon basic;
    std::cin >> basic;

    auto firstNonWhitespace = std::find_if_not(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), isspace);
    if (*firstNonWhitespace == std::iostream::traits_type::eof() or *firstNonWhitespace == int('n'))
    {
        throw "<INVALID COMMAND>";
    }
    if (!isspace(*firstNonWhitespace))
    {
        std::cin.setstate(std::ios_base::failbit);
        throw "<INVALID COMMAND>";
    }

    auto comparison = [&](const Polygon polygon)
        {
            bool result = std::greater<double>()(basic.getArea(), polygon.getArea());
            return result;
        };

    std::cout << std::count_if(polygons.begin(), polygons.end(), comparison) << std::endl;
}

void functors::same(std::vector<Polygon>& polygons)
{
    if (polygons.empty())
    {
        throw "<INVALID COMMAND>";
    }

    Polygon basic;
    std::cin >> basic;

    auto firstNonWhitespace = std::find_if_not(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), isspace);
    if (*firstNonWhitespace == std::iostream::traits_type::eof() or *firstNonWhitespace == int('n'))
    {
        throw "<INVALID COMMAND>";
    }
    if (!isspace(*firstNonWhitespace))
    {
        std::cin.setstate(std::ios_base::failbit);
        throw "<INVALID COMMAND>";
    }

    int count = 0;

    auto counter = [&](const Polygon tPolygon)
        {
            if (basic == tPolygon)
            {
                count++;
            }
            else
            {
                count = 0;
                return false;
            }
            return true;
        };
    count = std::count_if(polygons.begin(), polygons.end(), counter);
    std::cout << count << "\n";
}

void functors::echo()
{
    std::string input;
    std::cin >> input;
    std::cout << "ECHO: " << input << std::endl;
}

void functors::rightShapes(const std::vector<Polygon>& polygons)
{
    std::string input;
    std::cin >> input;
    double threshold = convertToInt(input);
    if (threshold <= 0)
    {
        throw "<INVALID COMMAND>";
    }

    auto count = [threshold](const Polygon& polygon)
    {
        return polygon.getArea() > threshold;
    };

    std::cout << std::count_if(polygons.begin(), polygons.end(), count) << std::endl;
}

