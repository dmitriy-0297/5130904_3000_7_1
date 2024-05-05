        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <functional>
        #include <cmath>
        #include <sstream>
        #include <limits>
        #include <iomanip>
        #include <stdexcept>
        #include <numeric>

        namespace tretyak {

            struct Point {
                int x, y;
                friend std::istream& operator>>(std::istream& is, Point& p) {
                    char ch1, ch2, ch3;
                    if (!(is >> ch1 >> p.x >> ch2 >> p.y >> ch3) || ch1 != '(' || ch2 != ';' || ch3 != ')') {
                        is.setstate(std::ios::failbit);
                    }
                    return is;
                }
            };

            struct Polygon {
                std::vector<Point> points;

                double area() const {
                    double totalArea = 0.0;
                    for (size_t i = 0; i < points.size(); i++) {
                        int j = (i + 1) % points.size();
                        totalArea += points[i].x * points[j].y;
                        totalArea -= points[j].x * points[i].y;
                    }
                    return std::fabs(totalArea / 2.0);
                }

                friend std::istream& operator>>(std::istream& is, Polygon& poly) {
                    int count;
                    if (!(is >> count) || count < 3) {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    poly.points.resize(count);
                    for (Point& p : poly.points) {
                        if (!(is >> p)) {
                            break;
                        }
                    }
                    return is;
                }
            };

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
                    try {
                        processLine(line);
                    }
                    catch (const std::exception& ex) {
                        std::cout << ex.what() << std::endl;
                    }
                }
            }

        private:
            std::vector<Polygon> polygons;

            void processLine(const std::string& line) {
                std::istringstream iss(line);
                std::string command, type;
                iss >> command >> type;
                if (command.empty() || type.empty()) {
                    throw std::runtime_error("<INVALID COMMAND>");
                }

                if (command == "AREA") {
                    handleAreaCommand(type);
                }
                else if (command == "COUNT") {
                    handleCountCommand(type);
                }
                else {
                    throw std::runtime_error("<INVALID COMMAND>");
                }
            }

            void handleAreaCommand(const std::string& type) {
                double result = 0.0;
                if (type == "MEAN") {
                    if (polygons.empty()) throw std::runtime_error("<INVALID COMMAND>");
                    result = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double acc, const Polygon& p) {
                        return acc + p.area();
                        }) / polygons.size();
                }
                else {
                    throw std::runtime_error("<INVALID COMMAND>");
                }
                std::cout << std::fixed << std::setprecision(1) << result << std::endl;
            }

            void handleCountCommand(const std::string& type) {
                if (type == "EVEN" || type == "ODD") {
                    int parity = (type == "EVEN") ? 0 : 1;
                    int count = std::count_if(polygons.begin(), polygons.end(), [parity](const Polygon& p) {
                        return static_cast<int>(p.points.size()) % 2 == parity;
                        });
                    std::cout << count << std::endl;
                }
                else {
                    int vertexCount = std::stoi(type);
                    if (vertexCount < 3) {
                        throw std::runtime_error("<INVALID COMMAND>");
                    }
                    int count = std::count_if(polygons.begin(), polygons.end(), [vertexCount](const Polygon& p) {
                        return static_cast<int>(p.points.size()) == vertexCount;
                        });
                    std::cout << count << std::endl;
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
