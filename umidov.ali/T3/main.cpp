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
            int x = 0;
            int y = 0;
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
            if (!(is >> ignore >> p.x >> ignore >> p.y >> ignore)) {
                is.setstate(std::ios::failbit);
            }
            return is;
        }

        std::istream& operator>>(std::istream& is, Polygon& poly) {
            int numVertices;
            char ch;
            if (!(is >> numVertices) || numVertices < 3) {
                is.setstate(std::ios::failbit);
                return is;
            }
            poly.points.clear();
            poly.points.reserve(numVertices);
            Point point;
            for (int i = 0; i < numVertices; ++i) {
                if (!(is >> ch >> point.x >> ch >> point.y >> ch)) {
                    is.setstate(std::ios::failbit);
                    break;
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

        void processCommands(std::vector<Polygon>& polygons) {
            std::string commandLine;
            while (getline(std::cin, commandLine)) {
                std::istringstream iss(commandLine);
                std::string command;
                iss >> command;

                if (command == "COUNT") {
                    std::string type;
                    iss >> type;
                    try {
                        int numVertices = std::stoi(type);
                        if (numVertices < 3) {
                            std::cout << "<INVALID COMMAND>" << std::endl;
                        }
                        else {
                            int count = std::count_if(polygons.begin(), polygons.end(), [numVertices](const Polygon& poly) {
                                return static_cast<int>(poly.points.size()) == numVertices;
                                });
                            std::cout << count << std::endl;
                        }
                    }
                    catch (const std::invalid_argument&) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
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
