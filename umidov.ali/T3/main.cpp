        #define _CRT_SECURE_NO_WARNINGS
        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <sstream>
        #include <algorithm>
        #include <cmath>
        #include <iomanip>
        #include <limits>
        #include <functional>

        struct Point
        {
            int x, y;
            bool operator==(const Point& other) const
            {
                return x == other.x && y == other.y;
            }
        };
        struct Polygon
        {
            std::vector<Point> points;

            double area() const
            {
                double total = 0.0;
                for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++)
                {
                    total += (points[j].x + points[i].x) * (points[j].y - points[i].y);
                }
                return std::abs(total) / 2.0;
            }
            size_t vertexCount() const
            {
                return points.size();
            }
        };
        bool parse_point(const std::string& str, Point& p)
        {
            return sscanf(str.c_str(), " (%d;%d)", &p.x, &p.y) == 2;
        }
        bool load_polygons(const char* filename, std::vector<Polygon>& polygons)
        {
            std::ifstream file(filename);
            if (!file)
            {
                std::cerr << "Could not open file." << std::endl;
                return false;
            }
            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                int vertices_count;
                if (!(iss >> vertices_count)) continue;
                Polygon poly;
                std::string point_str;
                while (vertices_count-- > 0 && iss >> point_str)
                {
                    Point p;
                    if (parse_point(point_str, p))
                    {
                        poly.points.push_back(p);
                    }
                }
                if (!poly.points.empty() && poly.points.size() == poly.vertexCount())
                {
                    polygons.push_back(poly);
                }
            }
            return true;
        }
        void handleCommands(const std::vector<Polygon>& polygons)
        {
            std::string command;
            while (std::cout << "> " && std::cin >> command)
            {
                if (command == "AREA")
                {
                    std::string type;
                    std::cin >> type;
                    double totalArea = 0.0;
                    int count = 0;
                    for (const auto& poly : polygons)
                    {
                        if (type == "MEAN" || (type == "EVEN" && poly.vertexCount() % 2 == 0) ||
                            (type == "ODD" && poly.vertexCount() % 2 != 0))
                        {
                            totalArea += poly.area();
                            ++count;
                        }
                    }
                    if (type == "MEAN" && count > 0)
                    {
                        std::cout << std::fixed << std::setprecision(1) << totalArea / count << std::endl;
                    }
                    else {
                        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
                    }
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }
        }
        int main(int argc, char* argv[])
        {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
                return 1;
            }
            std::vector<Polygon> polygons;
            if (!load_polygons(argv[1], polygons))
            {
                return 1;
            }
            handleCommands(polygons);
            return 0;
        }
