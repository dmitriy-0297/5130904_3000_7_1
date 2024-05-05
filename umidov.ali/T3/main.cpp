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
            };

            struct Polygon {
                std::vector<Point> points;
                double area() const {
                    double totalArea = 0.0;
                    for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
                        totalArea += (points[j].x + points[i].x) * (points[j].y - points[i].y);
                    }
                    return 0.5 * std::abs(totalArea);
                }
            };

            std::istream& operator>>(std::istream& is, Polygon& poly) {
                int numPoints = 0;
                is >> numPoints;
                poly.points.resize(numPoints);
                for (int i = 0; i < numPoints; ++i) {
                    poly.points[i].x = 0;
                    poly.points[i].y = 0;
                    is >> poly.points[i].x >> poly.points[i].y;
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
                    throw std::runtime_error("Unable to open file: " + filename);
                }
                Polygon poly;
                while (file >> poly) {
                    polygons.push_back(poly);
                }
            }

            void processCommands() {
                std::string line;
                while (std::getline(std::cin, line)) {
                    std::istringstream iss(line);
                    std::string command;
                    iss >> command;
                    if (command == "COUNT") {
                        std::string type;
                        iss >> type;
                        handleCountCommand(type);
                    }
                    else if (command == "AREA") {
                        std::string type;
                        iss >> type;
                        handleAreaCommand(type);
                    }
                    else if (command == "MAX") {
                        std::string type;
                        iss >> type;
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
                    int parity = (type == "EVEN") ? 0 : 1;
                    int count = std::count_if(polygons.begin(), polygons.end(), [parity](const Polygon& p) {
                        return static_cast<int>(p.points.size()) % 2 == parity;
                        });
                    std::cout << count << std::endl;
                }
                else {
                    try {
                        int vertexCount = std::stoi(type);
                        if (vertexCount < 3) {
                            std::cout << "<INVALID COMMAND>" << std::endl;
                        }
                        else {
                            int count = std::count_if(polygons.begin(), polygons.end(), [vertexCount](const Polygon& p) {
                                return static_cast<int>(p.points.size()) == vertexCount;
                                });
                            std::cout << count << std::endl;
                        }
                    }
                    catch (...) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                }
            }


            void handleAreaCommand(const std::string& type) {
                if (type == "MEAN") {
                    if (polygons.empty()) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                        return;
                    }
                    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double acc, const Polygon& p) {
                        return acc + p.area();
                        });
                    std::cout << std::fixed << std::setprecision(1) << (totalArea / polygons.size()) << std::endl;
                }
                else {
                    bool isEven = (type == "EVEN");
                    double totalArea = 0.0;
                    int count = 0;
                    for (const Polygon& p : polygons) {
                        if ((p.points.size() % 2 == 0) == isEven) {
                            totalArea += p.area();
                            count++;
                        }
                    }
                    if (count == 0) {
                        std::cout << "<INVALID COMMAND>" << std::endl;
                    }
                    else {
                        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
                    }
                }
            }

            void handleMaxCommand(const std::string& type) {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    return;
                }

                if (type == "AREA") {
                    auto maxIt = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
                        return a.area() < b.area();
                        });
                    std::cout << std::fixed << std::setprecision(1) << maxIt->area() << std::endl;
                }
                else if (type == "VERTEXES") {
                    auto maxIt = std::max_element(polygons.begin(), polygons.end(), [](const Polygon& a, const Polygon& b) {
                        return a.points.size() < b.points.size();
                        });
                    std::cout << maxIt->points.size() << std::endl;
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
