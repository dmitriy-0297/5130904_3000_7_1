        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <functional>
        #include <cmath>
        #include <sstream>
        #include <limits>
        #include <map>
        #include <numeric>
        #include <iomanip>

        struct Point {
            int x, y;
        };

        struct Polygon {
            std::vector<Point> points;

            bool operator==(const Polygon& other) const {
                if (points.size() != other.points.size()) return false;
                for (size_t i = 0; i < points.size(); ++i) {
                    if (points[i].x != other.points[i].x || points[i].y != other.points[i].y) return false;
                }
                return true;
            }
        };

        std::istream& operator>>(std::istream& is, Point& p) {
            char ignore;
            return is >> ignore >> p.x >> ignore >> p.y >> ignore;
        }

        std::istream& operator>>(std::istream& is, Polygon& poly) {
            int numVertices;
            char ch;
            is >> numVertices;
            poly.points.clear();
            for (int i = 0; i < numVertices; ++i) {
                Point point;
                if (!(is >> ch >> point.x >> ch >> point.y >> ch)) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                poly.points.push_back(point);
            }
            return is;
        }

        double polygonArea(const Polygon& poly) {
            double area = 0.0;
            int j = poly.points.size() - 1;
            for (size_t i = 0; i < poly.points.size(); i++) {
                area += (poly.points[j].x + poly.points[i].x) * (poly.points[j].y - poly.points[i].y);
                j = i;
            }
            return std::abs(area / 2.0);
        }

        std::vector<Polygon> readPolygons(const std::string& filename) {
            std::vector<Polygon> polygons;
            std::ifstream file(filename);
            if (!file) {
                throw std::runtime_error("Unable to open file");
            }
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                Polygon poly;
                if (iss >> poly) {
                    polygons.push_back(poly);
                }
            }
            return polygons;
        }

        void echoCommand(std::vector<Polygon>& polygons, const Polygon& inputPolygon) {
            int count = 0;
            for (size_t i = 0; i < polygons.size(); ++i) {
                if (polygons[i] == inputPolygon) {
                    polygons.insert(polygons.begin() + i + 1, inputPolygon);
                    i++;
                    count++;
                }
            }
            std::cout << count << std::endl;
        }
        void processCommands(std::vector<Polygon>& polygons) {
            std::string commandLine;
            while (getline(std::cin, commandLine)) {
                std::istringstream iss(commandLine);
                std::string command;
                iss >> command;

                if (command == "AREA") {
                    std::string param;
                    iss >> param;
                    if (param == "MEAN") {
                        double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            [](double acc, const Polygon& poly) { return acc + polygonArea(poly); });
                        std::cout << std::fixed << std::setprecision(1) << totalArea / polygons.size() << std::endl;
                    }
                    else if (param == "EVEN" || param == "ODD") {
                        bool isEven = (param == "EVEN");
                        double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            [isEven](double acc, const Polygon& poly) {
                                if ((poly.points.size() % 2 == 0) == isEven) {
                                    return acc + polygonArea(poly);
                                }
                                return acc;
                            });
                        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
                    }
                    else {
                        int numVertices = std::stoi(param);
                        double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            [numVertices](double acc, const Polygon& poly) {
                                if (poly.points.size() == static_cast<size_t>(numVertices)) {
                                    return acc + polygonArea(poly);
                                }
                                return acc;
                            });
                        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
                    }
                }
                else if (command == "ECHO") {
                    Polygon inputPolygon;
                    if (iss >> inputPolygon) {
                        echoCommand(polygons, inputPolygon);
                    }
                    else {
                        std::cout << "INVALID COMMAND" << std::endl;
                    }
                }
                else {
                    std::cout << "INVALID COMMAND" << std::endl;
                }
            }
        }

        int main(int argc, char** argv) {
            try {
                if (argc != 2) {
                    std::cerr << "Error: Filename not provided." << std::endl;
                    return EXIT_FAILURE;
                }

                std::vector<Polygon> polygons = readPolygons(argv[1]);
                processCommands(polygons);
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
