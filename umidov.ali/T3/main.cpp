        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <algorithm>
        #include <numeric>
        #include <sstream>
        #include <cmath>

        const std::string INVALID_COMMAND = "<INVALID COMMAND>";

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
                double sum = 0;
                size_t size = points.size();
                for (size_t i = 0; i < size; ++i) {
                    const Point& p1 = points[i];
                    const Point& p2 = points[(i + 1) % size];
                    sum += (p1.x * p2.y - p2.x * p1.y);
                }
                return std::abs(sum) / 2;
            }
        };

        class CommandProcessor {
        public:
            static void execute(std::vector<Polygon>& polygons, const std::string& command) {
                std::istringstream iss(command);
                std::string cmd;
                iss >> cmd;

                if (cmd == "AREA") {
                    std::string divisor;
                    iss >> divisor;
                    area(polygons, divisor);
                }
                else if (cmd == "MAX") {
                    max(polygons);
                }
                else if (cmd == "MIN") {
                    min(polygons);
                }
                else {
                    throw INVALID_COMMAND;
                }
            }

        private:
            static void area(const std::vector<Polygon>& polygons, const std::string& divisor) {
                if (divisor == "MEAN") {
                    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        [](double acc, const Polygon& p) { return acc + p.area(); });
                    std::cout << std::fixed << (totalArea / polygons.size()) << "\n";
                }
                else {
                    int div = (divisor == "EVEN" || divisor == "ODD") ? 2 : std::stoi(divisor);
                    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        [div](double acc, const Polygon& p) {
                            return acc + ((p.points.size() % div == 0) ? p.area() : 0);
                        });
                    std::cout << std::fixed << totalArea << "\n";
                }
            }

            static void max(const std::vector<Polygon>& polygons) {
                if (polygons.empty())
                    throw INVALID_COMMAND;
                auto maxArea = std::max_element(polygons.begin(), polygons.end(),
                    [](const Polygon& p1, const Polygon& p2) { return p1.area() < p2.area(); });
                std::cout << std::fixed << maxArea->area() << "\n";
            }

            static void min(const std::vector<Polygon>& polygons) {
                if (polygons.empty())
                    throw INVALID_COMMAND;
                auto minArea = std::min_element(polygons.begin(), polygons.end(),
                    [](const Polygon& p1, const Polygon& p2) { return p1.area() < p2.area(); });
                std::cout << std::fixed << minArea->area() << "\n";
            }
        };

        int main(int argc, char* argv[]) {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " <filename>\n";
                return EXIT_FAILURE;
            }

            std::ifstream file(argv[1]);
            if (!file) {
                std::cerr << "Error: failed to open the file.\n";
                return EXIT_FAILURE;
            }

            std::vector<Polygon> polygons;
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                Polygon poly;
                int x, y;
                while (iss >> x >> y) {
                    poly.points.push_back(Point(x, y));
                }
                if (poly.points.size() >= 3) {
                    polygons.push_back(poly);
                }
            }

            try {
                std::string command;
                while (std::getline(std::cin, command) && !command.empty()) {
                    CommandProcessor::execute(polygons, command);
                }
            }
            catch (const std::string& error) {
                std::cout << error << "\n";
                return EXIT_FAILURE;
            }

            return EXIT_SUCCESS;
        }
