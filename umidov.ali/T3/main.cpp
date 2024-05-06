        #include <iostream>
        #include <fstream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <cmath>
        #include <sstream>
        #include <limits>
        #include <iomanip>
        #include <stdexcept>
        #include <numeric>
        #include <functional>
        #include <cctype>

        namespace vectonix {

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
                        totalArea += points[i].x * points[j].y - points[j].x * points[i].y;
                    }
                    return std::fabs(totalArea / 2.0);
                }

                friend std::istream& operator>>(std::istream& is, Polygon& poly) {
                    int count;
                    is >> count;
                    if (count < 3) {
                        is.setstate(std::ios::failbit);
                        return is;
                    }
                    poly.points.resize(count);
                    for (Point& p : poly.points) {
                        is >> p;
                        if (!is) break;
                    }
                    return is;
                }
            };

            void area(const std::vector<Polygon>& data);
            void min(const std::vector<Polygon>& data);
            void max(const std::vector<Polygon>& data);
            void count(const std::vector<Polygon>& data);
            void echo(std::vector<Polygon>& data);
            void inframe(const std::vector<Polygon>& data);
        }

        using namespace vectonix;
        using namespace std::placeholders;

        void vectonix::area(const std::vector<Polygon>& data) {

        }

        void vectonix::min(const std::vector<Polygon>& data) {

        }

        void vectonix::max(const std::vector<Polygon>& data) {

        }

        void vectonix::count(const std::vector<Polygon>& data) {

        }

        void vectonix::echo(std::vector<Polygon>& data) {

        }

        void vectonix::inframe(const std::vector<Polygon>& data) {

        }

        int main(int argc, char* argv[]) {
            if (argc != 2) {
                std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
                return EXIT_FAILURE;
            }
            std::string fileName = argv[1];
            std::ifstream file(fileName);
            if (!file) {
                std::cerr << "Error: file didn't open\n";
                return EXIT_FAILURE;
            }

            std::cout << std::setprecision(1) << std::fixed;
            std::vector<vectonix::Polygon> vec;
            while (!file.eof()) {
                std::copy(
                    std::istream_iterator<vectonix::Polygon>(file),
                    std::istream_iterator<vectonix::Polygon>(),
                    std::back_inserter(vec)
                );
                if (!file.eof() && file.fail()) {
                    file.clear();
                    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            while (!std::cin.eof()) {
                std::cin.clear();
                std::string command;
                std::cin >> command;
                try {
                    if (command == "AREA") vectonix::area(vec);
                    else if (command == "MIN") vectonix::min(vec);
                    else if (command == "MAX") vectonix::max(vec);
                    else if (command == "COUNT") vectonix::count(vec);
                    else if (command == "ECHO") vectonix::echo(vec);
                    else if (command == "INFRAME") vectonix::inframe(vec);
                    else if (!std::cin.eof()) {
                        throw std::runtime_error("<INVALID COMMAND>");
                    }
                }
                catch (std::exception& ex) {
                    std::cout << ex.what() << '\n';
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            return 0;
        }
