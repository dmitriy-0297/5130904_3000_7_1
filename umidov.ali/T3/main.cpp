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

        const std::string I_C = "<INVALID COMMAND>";

        namespace tretyak {
            struct Point {
                int x_, y_;

                Point(int x = 0, int y = 0) : x_(x), y_(y) {}

                bool operator!=(const Point& other) const {
                    return x_ != other.x_ || y_ != other.y_;
                }
            };

            struct Polygon {
                std::vector<Point> points;

                double area() const {
                    double accum = 0.0;
                    for (size_t i = 0; i < points.size(); i++) {
                        const auto& current = points[i];
                        const auto& next = points[(i + 1) % points.size()];
                        accum += (current.x_ * next.y_ - next.x_ * current.y_);
                    }
                    return std::abs(accum * 0.5);
                }

                bool operator==(const Polygon& other) const {
                    if (points.size() != other.points.size())
                        return false;
                    for (size_t i = 0; i < points.size(); i++) {
                        if (points[i] != other.points[i])
                            return false;
                    }
                    return true;
                }
            };

            std::istream& operator>>(std::istream& in, Point& elem) {
                return in >> elem.x_ >> elem.y_;
            }

            std::istream& operator>>(std::istream& in, Polygon& elem) {
                int size;
                in >> size;
                elem.points.resize(size);
                for (int i = 0; i < size; i++) {
                    in >> elem.points[i];
                }
                return in;
            }

            std::ostream& operator<<(std::ostream& out, const Point& elem) {
                return out << '(' << elem.x_ << ';' << elem.y_ << ')';
            }

            std::ostream& operator<<(std::ostream& out, const Polygon& elem) {
                out << elem.points.size() << ' ';
                for (const auto& point : elem.points) {
                    out << point << ' ';
                }
                return out;
            }
        }

        namespace cmd {
            int validStringToInt(const std::string& str) {
                char* end;
                long sInt = strtol(str.c_str(), &end, 10);
                if (*end != '\0' || end == str.c_str()) {
                    return -1;
                }
                return static_cast<int>(sInt);
            }

            void area(std::vector<tretyak::Polygon>& value, const std::string str) {
                int data = validStringToInt(str);
                if (data == -1) {
                    if (str == "EVEN") {
                        std::cout << std::accumulate(value.begin(), value.end(), 0.0, [](double acc, const tretyak::Polygon& p) {
                            return acc + (p.points.size() % 2 == 0 ? p.area() : 0);
                            }) << "\n";
                    }
                    else if (str == "ODD") {
                        std::cout << std::accumulate(value.begin(), value.end(), 0.0, [](double acc, const tretyak::Polygon& p) {
                            return acc + (p.points.size() % 2 != 0 ? p.area() : 0);
                            }) << "\n";
                    }
                    else if (str == "MEAN") {
                        std::cout << (value.empty() ? 0.0 : std::accumulate(value.begin(), value.end(), 0.0, [](double acc, const tretyak::Polygon& p) {
                            return acc + p.area();
                            }) / value.size()) << "\n";
                    }
                    else {
                        throw I_C;
                    }
                }
                else if (data > 2) {
                    std::cout << std::accumulate(value.begin(), value.end(), 0.0, [data](double acc, const tretyak::Polygon& p) {
                        return acc + (p.points.size() % data == 0 ? p.area() : 0);
                        }) << "\n";
                }
                else {
                    throw I_C;
                }
            }
            void max(std::vector<tretyak::Polygon>& value, const std::string str) {
                if (str == "AREA") {
                    std::cout << std::max_element(value.begin(), value.end(),
                        [](const tretyak::Polygon& a, const tretyak::Polygon& b) {
                            return a.area() < b.area();
                        })->area() << "\n";
                }
                else if (str == "VERTEXES") {
                    std::cout << std::max_element(value.begin(), value.end(),
                        [](const tretyak::Polygon& a, const tretyak::Polygon& b) {
                            return a.points.size() < b.points.size();
                        })->points.size() << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void min(std::vector<tretyak::Polygon>& value, const std::string str) {
                if (str == "AREA") {
                    std::cout << std::min_element(value.begin(), value.end(),
                        [](const tretyak::Polygon& a, const tretyak::Polygon& b) {
                            return a.area() < b.area();
                        })->area() << "\n";
                }
                else if (str == "VERTEXES") {
                    std::cout << std::min_element(value.begin(), value.end(),
                        [](const tretyak::Polygon& a, const tretyak::Polygon& b) {
                            return a.points.size() < b.points.size();
                        })->points.size() << "\n";
                }
                else {
                    throw I_C;
                }
            }



            void count(std::vector<tretyak::Polygon>& value, const std::string str) {
                int data = validStringToInt(str);
                if (data == -1) {
                    if (str == "EVEN") {
                        std::cout << std::count_if(value.begin(), value.end(), [](const tretyak::Polygon& p) {
                            return p.points.size() % 2 == 0;
                            }) << "\n";
                    }
                    else if (str == "ODD") {
                        std::cout << std::count_if(value.begin(), value.end(), [](const tretyak::Polygon& p) {
                            return p.points.size() % 2 != 0;
                            }) << "\n";
                    }
                }
                else if (data > 2) {
                    std::cout << std::count_if(value.begin(), value.end(), [data](const tretyak::Polygon& p) {
                        return p.points.size() % data == 0;
                        }) << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void lessArea(std::vector<tretyak::Polygon>& value) {
                if (value.empty()) throw I_C;
                tretyak::Polygon mainEl;
                std::cin >> mainEl;

                int count = std::count_if(value.begin(), value.end(), [&](const tretyak::Polygon& p) {
                    return mainEl.area() > p.area();
                    });
                std::cout << count << "\n";
            }

            void maxSeq(std::vector<tretyak::Polygon>& value) {
                if (value.empty()) throw I_C;
                tretyak::Polygon mainEl;
                std::cin >> mainEl;

                int maxCount = 0;
                int currentCount = 0;
                for (const auto& polygon : value) {
                    if (polygon == mainEl) {
                        currentCount++;
                        maxCount = std::max(maxCount, currentCount);
                    }
                    else {
                        currentCount = 0;
                    }
                }
                std::cout << maxCount << "\n";
            }
        }

        int main(int argc, char* argv[]) {
            if (argc != 2) {
                std::cerr << "Usage: program_name <filename>" << "\n";
                return EXIT_FAILURE;
            }

            std::ifstream file(argv[1]);
            if (!file) {
                std::cerr << "Error: File did not open." << "\n";
                return EXIT_FAILURE;
            }

            std::vector<tretyak::Polygon> polygons;
            tretyak::Polygon polygon;
            while (file >> polygon) {
                polygons.push_back(polygon);
            }

            try {
                std::string command, parameter;
                while (std::cin >> command >> parameter && !std::cin.eof()) {
                    if (command == "AREA") cmd::area(polygons, parameter);
                    else if (command == "MAX") cmd::max(polygons, parameter);
                    else if (command == "MIN") cmd::min(polygons, parameter);
                    else if (command == "COUNT") cmd::count(polygons, parameter);
                    else if (command == "LESSAREA") cmd::lessArea(polygons);
                    else if (command == "MAXSEQ") cmd::maxSeq(polygons);
                    else throw std::string(I_C);
                }
            }
            catch (const std::string& e) {
                std::cout << e << "\n";
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
