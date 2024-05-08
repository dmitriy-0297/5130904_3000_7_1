        #include <iostream>
        #include <vector>
        #include <algorithm>
        #include <functional>
        #include <numeric>
        #include <iomanip>
        #include <string>
        #include <sstream>
        #include <fstream>
        #include <limits>
        #include <cmath>

        namespace geometry {
            struct Point {
                int x, y;
                Point(int x = 0, int y = 0) : x(x), y(y) {}
                bool operator!=(const Point& other) const {
                    return x != other.x || y != other.y;
                }
            };

            struct Polygon {
                std::vector<Point> points;
                double area() const {
                    double total = 0.0;
                    for (size_t i = 0; i < points.size(); ++i) {
                        size_t next = (i + 1) % points.size();
                        total += points[i].x * points[next].y;
                        total -= points[i].y * points[next].x;
                    }
                    return std::abs(total / 2.0);
                }
            };

            std::istream& operator>>(std::istream& in, Point& p) {
                char ch1, ch2, ch3;
                in >> ch1 >> p.x >> ch2 >> p.y >> ch3;
                return in;
            }

            std::istream& operator>>(std::istream& in, Polygon& poly) {
                int size;
                in >> size;
                poly.points.resize(size);
                for (int i = 0; i < size; ++i) {
                    in >> poly.points[i];
                }
                return in;
            }
        }

        std::vector<geometry::Polygon> loadPolygons(const std::string& filename) {
            std::vector<geometry::Polygon> polygons;
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Cannot open file: " << filename << std::endl;
                return polygons;
            }

            geometry::Polygon poly;
            while (file >> poly) {
                polygons.push_back(poly);
            }

            file.close();
            return polygons;
        }

        int countPolygonsWithVertexCount(const std::vector<geometry::Polygon>& polygons, int count) {
            return std::count_if(polygons.begin(), polygons.end(), [count](const geometry::Polygon& p) {
                return p.points.size() == count;
                });
        }

        int countEvenOddPolygons(const std::vector<geometry::Polygon>& polygons, bool countEven) {
            return std::count_if(polygons.begin(), polygons.end(), [countEven](const geometry::Polygon& p) {
                return (p.points.size() % 2 == 0) == countEven;
                });
        }

        double totalArea(const std::vector<geometry::Polygon>& polygons, bool countEven) {
            double area = 0.0;
            for (const auto& poly : polygons) {
                if ((poly.points.size() % 2 == 0) == countEven) {
                    area += poly.area();
                }
            }
            return area;
        }

        int main(int argc, char* argv[]) {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
                return EXIT_FAILURE;
            }

            auto polygons = loadPolygons(argv[1]);
            std::string line;
            while (std::getline(std::cin, line)) {
                std::istringstream iss(line);
                std::string command;
                iss >> command;

                if (command == "COUNT") {
                    std::string type;
                    iss >> type;
                    if (type == "EVEN") {
                        std::cout << countEvenOddPolygons(polygons, true) << std::endl;
                    }
                    else if (type == "ODD") {
                        std::cout << countEvenOddPolygons(polygons, false) << std::endl;
                    }
                    else {
                        int vertexCount = std::stoi(type);
                        std::cout << countPolygonsWithVertexCount(polygons, vertexCount) << std::endl;
                    }
                }
                else if (command == "AREA") {
                    std::string type;
                    iss >> type;
                    if (type == "EVEN") {
                        std::cout << totalArea(polygons, true) << std::endl;
                    }
                    else if (type == "ODD") {
                        std::cout << totalArea(polygons, false) << std::endl;
                    }
                    else {
                        int vertexCount = std::stoi(type);
                        double area = 0.0;
                        for (const auto& poly : polygons) {
                            if (poly.points.size() == vertexCount) {
                                area += poly.area();
                            }
                        }
                        std::cout << std::fixed << std::setprecision(1) << area << std::endl;
                    }
                }
                else if (command == "MAX") {
                    std::string type;
                    iss >> type;
                    if (type == "AREA") {
                        double maxArea = std::numeric_limits<double>::lowest();
                        for (const auto& poly : polygons) {
                            double area = poly.area();
                            if (area > maxArea) {
                                maxArea = area;
                            }
                        }
                        std::cout << std::fixed << std::setprecision(1) << maxArea << std::endl;
                    }
                    else if (type == "VERTEXES" || type == "VERTICES") {
                        int maxVertices = std::numeric_limits<int>::lowest();
                        for (const auto& poly : polygons) {
                            int vertices = poly.points.size();
                            if (vertices > maxVertices) {
                                maxVertices = vertices;
                            }
                        }
                        std::cout << maxVertices << std::endl;
                    }
                    else {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                }
                else if (command == "AREA MEAN") {
                    if (polygons.empty()) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                    else {
                        double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            [](double sum, const geometry::Polygon& poly) {
                                return sum + poly.area();
                            });
                        double mean = total / polygons.size();
                        std::cout << std::fixed << std::setprecision(1) << mean << std::endl;
                    }
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }
            return EXIT_SUCCESS;
        }
