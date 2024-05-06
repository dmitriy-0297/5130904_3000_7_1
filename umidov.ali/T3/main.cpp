        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <functional>
        #include <numeric>
        #include <iomanip>
        #include <sstream>
        #include <iterator>
        #include <exception>
        #include <limits>
        #include <cmath>

        const std::string INVALID_COMMAND = "<INVALID COMMAND>";
        const std::string MEAN = "MEAN";
        const std::string EVEN = "EVEN";
        const std::string ODD = "ODD";

        namespace tretyak {
            struct Point {
                int x, y;

                Point(int x = 0, int y = 0) : x(x), y(y) {}

                friend std::istream& operator>>(std::istream& in, Point& p) {
                    in >> p.x >> p.y;
                    return in;
                }

                friend std::ostream& operator<<(std::ostream& out, const Point& p) {
                    out << '(' << p.x << ", " << p.y << ')';
                    return out;
                }
            };

            class Polygon {
                std::vector<Point> points;

            public:
                void addPoint(const Point& point) {
                    points.push_back(point);
                }

                double area() const {
                    double area = 0.0;
                    for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
                        area += (points[j].x + points[i].x) * (points[j].y - points[i].y);
                    }
                    return std::abs(area / 2.0);
                }

                size_t vertexCount() const {
                    return points.size();
                }

                friend std::istream& operator>>(std::istream& in, Polygon& polygon) {
                    int count;
                    in >> count;
                    Point temp;
                    for (int i = 0; i < count; i++) {
                        in >> temp;
                        polygon.addPoint(temp);
                    }
                    return in;
                }

                friend std::ostream& operator<<(std::ostream& out, const Polygon& polygon) {
                    out << polygon.points.size() << ": ";
                    for (const auto& point : polygon.points) {
                        out << point << ' ';
                    }
                    return out;
                }
            };
        }

        namespace cmd {
            using namespace tretyak;

            double calculateTotalArea(const std::vector<Polygon>& polygons, std::function<bool(const Polygon&)> predicate) {
                return std::accumulate(polygons.begin(), polygons.end(), 0.0, [&predicate](double total, const Polygon& polygon) {
                    return total + (predicate(polygon) ? polygon.area() : 0);
                    });
            }

            void processCommands(const std::vector<Polygon>& polygons, const std::string& command, const std::string& parameter) {
                if (command == "AREA") {
                    if (parameter == EVEN) {
                        std::cout << "Total area of polygons with an even number of vertices: "
                            << calculateTotalArea(polygons, [](const Polygon& p) { return p.vertexCount() % 2 == 0; }) << "\n";
                    }
                    else if (parameter == ODD) {
                        std::cout << "Total area of polygons with an odd number of vertices: "
                            << calculateTotalArea(polygons, [](const Polygon& p) { return p.vertexCount() % 2 != 0; }) << "\n";
                    }
                    else if (parameter == MEAN) {
                        double totalArea = calculateTotalArea(polygons, [](const Polygon&) { return true; });
                        std::cout << "Mean area of polygons: " << (polygons.empty() ? 0 : totalArea / polygons.size()) << "\n";
                    }
                    else {
                        std::cerr << INVALID_COMMAND << "\n";
                    }
                }
                else {
                    std::cerr << INVALID_COMMAND << "\n";
                }
            }
        }

        int main(int argc, char* argv[]) {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " <filename>\n";
                return EXIT_FAILURE;
            }

            std::ifstream file(argv[1]);
            if (!file) {
                std::cerr << "Error opening file: " << argv[1] << "\n";
                return EXIT_FAILURE;
            }

            std::vector<tretyak::Polygon> polygons;
            tretyak::Polygon polygon;
            while (file >> polygon) {
                polygons.push_back(polygon);
            }

            std::string command, parameter;
            while (std::cout << "Enter command and parameter: " && std::cin >> command >> parameter) {
                try {
                    cmd::processCommands(polygons, command, parameter);
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
            }

            return EXIT_SUCCESS;
        }
