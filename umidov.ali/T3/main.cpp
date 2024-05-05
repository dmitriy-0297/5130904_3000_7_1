        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <functional>
        #include <cmath>
        #include <sstream>
        #include <iomanip>
        #include <stdexcept>
        #include <numeric>
        #include <cctype>

        namespace tretyak {
            struct Point {
                int x, y;
                Point() : x(0), y(0) {}
            };

            struct Polygon {
                std::vector<Point> points;

                double area() const {
                    if (points.size() < 3) return 0.0;
                    double totalArea = 0.0;
                    for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
                        totalArea += (points[j].x + points[i].x) * (points[j].y - points[i].y);
                    }
                    return 0.5 * std::abs(totalArea);
                }
            };

            std::istream& operator>>(std::istream& is, Polygon& poly) {
                int numPoints;
                is >> numPoints;
                if (is.fail() || numPoints < 3) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
                poly.points.resize(numPoints);
                for (int i = 0; i < numPoints; ++i) {
                    is >> poly.points[i].x >> poly.points[i].y;
                    if (is.fail()) {
                        return is;
                    }
                }
                return is;
            }
        }

        using namespace tretyak;

        class CommandProcessor {
        public:
            explicit CommandProcessor(const std::string& filename) {
                std::ifstream file(filename);
                if (!file) {
                    std::cerr << "Error opening file: " << filename << std::endl;
                    throw std::runtime_error("File open failed");
                }
                Polygon poly;
                while (file >> poly) {
                    polygons.push_back(poly);
                }
                if (file.bad()) {
                    throw std::runtime_error("Error reading from file");
                }
            }

            void processCommands() {
                std::string line;
                while (std::getline(std::cin, line)) {
                    std::istringstream iss(line);
                    std::string command, type;
                    iss >> command >> type;
                    if (command.empty()) continue;

                    if (command == "COUNT") {
                        handleCountCommand(type);
                    }
                    else if (command == "AREA") {
                        handleAreaCommand(type);
                    }
                    else if (command == "MAX") {
                        handleMaxCommand(type);
                    }
                    else {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                }
            }

        private:
            std::vector<Polygon> polygons;

            void handleCountCommand(const std::string& type) {
                if (type == "EVEN" || type == "ODD") {
                    auto parity = static_cast<std::vector<Point>::size_type>((type == "EVEN") ? 0 : 1);
                    int count = std::count_if(polygons.begin(), polygons.end(), [parity](const Polygon& p) {
                        return (p.points.size() % 2 == parity);
                        });
                    std::cout << count << std::endl;
                }
                else {
                    try {
                        auto vertexCount = static_cast<std::vector<Point>::size_type>(std::stoi(type));
                        int count = std::count_if(polygons.begin(), polygons.end(), [vertexCount](const Polygon& p) {
                            return (p.points.size() == vertexCount);
                            });
                        std::cout << count << std::endl;
                    }
                    catch (...) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                }
            }


            void handleAreaCommand(const std::string& type) {
                if (type != "MEAN" || polygons.empty()) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }
                double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double acc, const Polygon& p) { return acc + p.area(); });
                std::cout << std::fixed << std::setprecision(1) << (totalArea / polygons.size()) << std::endl;
            }

            void handleMaxCommand(const std::string& type) {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }

                if (type == "AREA") {
                    auto maxIt = std::max_element(polygons.begin(), polygons.end(),
                        [](const Polygon& a, const Polygon& b) {
                            return a.area() < b.area();
                        });

                    if (maxIt != polygons.end()) {
                        std::cout << std::fixed << std::setprecision(1) << maxIt->area() << std::endl;
                    }
                    else {
                        std::cout << "No maximum area found." << std::endl;
                    }
                }
                else if (type == "VERTEXES") {
                    auto maxIt = std::max_element(polygons.begin(), polygons.end(),
                        [](const Polygon& a, const Polygon& b) {
                            return a.points.size() < b.points.size();
                        });

                    if (maxIt != polygons.end()) {
                        std::cout << maxIt->points.size() << std::endl;
                    }
                    else {
                        std::cout << "No maximum vertices found." << std::endl;
                    }
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

        };

        int main(int argc, char** argv) {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
                return EXIT_FAILURE;
            }
            try {
                CommandProcessor cmd(argv[1]);
                cmd.processCommands();
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
