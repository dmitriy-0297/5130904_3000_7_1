    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <algorithm>
    #include <functional>
    #include <numeric>
    #include <iomanip>
    #include <limits>
    #include <string>
    #include <sstream>
    #include <iterator>
    #include <exception>
    #include <cctype>

    const std::string I_C = "<INVALID COMMAND>";
    namespace tretyak
    {
        struct Point
        {
            int x, y;
            Point(int x = 0, int y = 0) : x(x), y(y) {}

            bool operator!=(const Point& other) const
            {
                return x != other.x || y != other.y;
            }
        };

        struct Polygon
        {
            std::vector<Point> points;

            double area() const {
                double accum = 0.0;
                for (size_t i = 0; i < points.size(); i++)
                {
                    const auto& current = points[i];
                    const auto& next = points[(i + 1) % points.size()];
                    accum += (current.x * next.y - next.x * current.y);
                }
                return std::abs(accum * 0.5);
            }

            bool operator==(const Polygon& other) const
            {
                if (points.size() != other.points.size())
                    return false;
                for (size_t i = 0; i < points.size(); i++)
                {
                    if (points[i] != other.points[i])
                        return false;
                }
                return true;
            }
        };

        std::istream& operator>>(std::istream& in, Point& elem)
        {
            in >> elem.x >> elem.y;
            return in;
        }

        std::ostream& operator<<(std::ostream& op, const Point& elem)
        {
            op << "(" << elem.x << ";" << elem.y << ")";
            return op;
        }

        std::istream& operator>>(std::istream& in, Polygon& elem)
        {
            int tSize;
            in >> tSize;
            elem.points.resize(tSize);
            for (int i = 0; i < tSize; i++)
            {
                in >> elem.points[i];
            }
            return in;
        }

        std::ostream& operator<<(std::ostream& op, const Polygon& elem)
        {
            op << elem.points.size() << " ";
            for (const auto& point : elem.points)
            {
                op << point << " ";
            }
            return op;
        }
    }
    namespace cmd
    {
        int validStringToInt(const std::string& str)
        {
            char* end;
            int sInt = strtol(str.c_str(), &end, 10);
            if (*end != '\0' || end == str.c_str())
            {
                return -1;
            }
            return sInt;
        }

        void area(std::vector<tretyak::Polygon>& value, const std::string& str)
        {
            int data = validStringToInt(str);
            if (data == -1)
            {
                if (str == "EVEN" || str == "ODD")
                {
                    int parity = str == "ODD" ? 1 : 0;
                    double result = std::accumulate(value.begin(), value.end(), 0.0, [parity](double acc, const tretyak::Polygon& p)
                        {
                        return acc + (p.points.size() % 2 == parity ? p.area() : 0);
                        });
                    std::cout << std::fixed << std::setprecision(1) << result << "\n";
                }
                else if (str == "MEAN" && !value.empty())
                {
                    double totalArea = std::accumulate(value.begin(), value.end(), 0.0, [](double acc, const tretyak::Polygon& p)
                        {
                        return acc + p.area();
                        });
                    std::cout << std::fixed << std::setprecision(1) << totalArea / value.size() << "\n";
                }
                else
                {
                    throw std::string(I_C);
                }
            }
            else if (data > 2)
            {
                double result = std::accumulate(value.begin(), value.end(), 0.0, [data](double acc, const tretyak::Polygon& p)
                    {
                    return acc + (p.points.size() == data ? p.area() : 0);
                    });
                std::cout << std::fixed << std::setprecision(1) << result << "\n";
            }
            else
            {
                throw std::string(I_C);
            }
        }

        void max(std::vector<tretyak::Polygon>& value, const std::string& str)
        {
            if (value.empty())
            {
                throw std::string(I_C);
            }
            if (str == "AREA")
            {
                auto maxArea = *std::max_element(value.begin(), value.end(),
                    [](const tretyak::Polygon& p1, const tretyak::Polygon& p2)
                    {
                        return p1.area() < p2.area();
                    });
                std::cout << std::fixed << std::setprecision(1) << maxArea.area() << "\n";
            }
            else if (str == "VERTEXES")
            {
                auto maxVertexes = *std::max_element(value.begin(), value.end(),
                    [](const tretyak::Polygon& p1, const tretyak::Polygon& p2)
                    {
                        return p1.points.size() < p2.points.size();
                    });
                std::cout << maxVertexes.points.size() << "\n";
            }
            else
            {
                throw std::string(I_C);
            }
        }

        void min(std::vector<tretyak::Polygon>& value, const std::string& str)
        {
            if (value.empty())
            {
                throw std::string(I_C);
            }
            if (str == "AREA")
            {
                auto minArea = *std::min_element(value.begin(), value.end(),
                    [](const tretyak::Polygon& p1, const tretyak::Polygon& p2)
                    {
                        return p1.area() < p2.area();
                    });
                std::cout << std::fixed << std::setprecision(1) << minArea.area() << "\n";
            }
            else if (str == "VERTEXES")
            {
                auto minVertexes = *std::min_element(value.begin(), value.end(),
                    [](const tretyak::Polygon& p1, const tretyak::Polygon& p2)
                    {
                        return p1.points.size() < p2.points.size();
                    });
                std::cout << minVertexes.points.size() << "\n";
            }
            else
            {
                throw std::string(I_C);
            }
        }
    }
    int main(int argc, char* argv[])
    {
        if (argc != 2)
        {
            std::cerr << "Usage: program_name <filename>" << "\n";
            return EXIT_FAILURE;
        }
        std::string fileName = argv[1];
        std::ifstream file(fileName);
        if (!file)
        {
            std::cerr << "Error: file didn't open" << "\n";
            return EXIT_FAILURE;
        }
        std::vector<tretyak::Polygon> value;
        tretyak::Polygon poly;
        while (file >> poly)
        {
            value.push_back(poly);
        }
        try
        {
            std::string str, cmd1, cmd2;
            while (std::getline(std::cin, str) && !str.empty())
            {
                std::istringstream iss(str);
                iss >> cmd1 >> cmd2;
                if (cmd1 == "AREA")
                {
                    cmd::area(value, cmd2);
                }
                else if (cmd1 == "MAX")
                {
                    cmd::max(value, cmd2);
                }
                else if (cmd1 == "MIN")
                {
                    cmd::min(value, cmd2);
                }
                else
                {
                    throw std::string(I_C);
                }
            }
            return EXIT_SUCCESS;
        }
        catch (const std::string& e)
        {
            std::cout << e << "\n";
            return EXIT_FAILURE;
        }
    }
