        #include <iostream>
        #include <vector>
        #include <string>
        #include <algorithm>
        #include <functional>
        #include <numeric>
        #include <iomanip>
        #include <sstream>
        #include <iterator>
        #include <fstream>
        #include <limits>
        #include <exception>


        namespace geometry {
            struct Point {
                int x_, y_;
                Point(int x = 0, int y = 0) : x_(x), y_(y) {}
                bool operator!=(const Point& otherEl) const;
            };

            struct Polygon {
                std::vector<Point> points;
                double area() const;
                bool operator==(const Polygon& otherEl) const;
            };

            struct DelimIO {
                std::string delim_;
                DelimIO(const std::string delim) : delim_(delim) {}
            };

            std::istream& operator>>(std::istream& in, Point& elem);
            std::istream& operator>>(std::istream& in, Polygon& elem);
            std::istream& operator>>(std::istream& in, DelimIO&& elem);
            std::ostream& operator<<(std::ostream& op, const Point& elem);
            std::ostream& operator<<(std::ostream& op, const Polygon& elem);
        }

        bool geometry::Point::operator!=(const Point& otherEl) const {
            return (this->x_ != otherEl.x_ || this->y_ != otherEl.y_);
        }

        double geometry::Polygon::area() const {
            double accum = 0.0;
            for (size_t i = 0; i < points.size(); i++) {
                const auto& current = points[i];
                const auto& next = points[(i + 1) % points.size()];
                accum += (current.x_ * next.y_ - next.x_ * current.y_);
            }
            return std::abs(accum * 0.5);
        }

        bool geometry::Polygon::operator==(const Polygon& otherEl) const {
            if (this->points.size() != otherEl.points.size())
                return false;
            for (size_t i = 0; i < this->points.size(); i++) {
                if (this->points[i] != otherEl.points[i])
                    return false;
            }
            return true;
        }

        std::istream& geometry::operator>>(std::istream& in, geometry::Point& elem) {
            std::istream::sentry sentry(in);
            if (!sentry)
                return in;
            in >> geometry::DelimIO("(") >> elem.x_ >> geometry::DelimIO(";") >> elem.y_ >> geometry::DelimIO(")");
            return in;
        }

        std::istream& geometry::operator>>(std::istream& in, geometry::Polygon& elem) {
            std::istream::sentry sentry(in);
            if (!sentry)
                return in;
            int tSize = 0;
            in >> tSize;
            if (tSize >= 3) {
                elem.points.clear();
                elem.points.resize(tSize);
                for (int i = 0; i < tSize; i++) {
                    in >> elem.points[i];
                }
            }
            else {
                in.setstate(std::ios_base::failbit);
            }
            return in;
        }

        std::istream& geometry::operator>>(std::istream& in, geometry::DelimIO&& elem) {
            std::istream::sentry sentry(in);
            if (!sentry)
                return in;
            std::string del;
            in >> std::setw(1) >> del;
            if (!in || del != elem.delim_) {
                in.setstate(std::ios_base::failbit);
            }
            return in;
        }

        std::ostream& geometry::operator<<(std::ostream& op, const geometry::Point& elem) {
            std::ostream::sentry sentry(op);
            if (!sentry)
                return op;
            op << "(" << elem.x_ << ";" << elem.y_ << ")";
            return op;
        }

        std::ostream& geometry::operator<<(std::ostream& op, const geometry::Polygon& elem) {
            std::ostream::sentry sentry(op);
            if (!sentry)
                return op;
            op << elem.points.size() << " ";
            for (size_t i = 0; i < elem.points.size(); i++) {
                op << elem.points[i] << " ";
            }
            return op;
        }

        namespace cmd {
            const std::string I_C = "<INVALID COMMAND>";

            int validStringToInt(std::string str) {
                char* end;
                int sInt = strtol(str.c_str(), &end, 10);
                if (*end != '\0' || end == str.c_str())
                    return -1;
                return static_cast<int>(sInt);
            }

            void area(std::vector<geometry::Polygon>& value, const std::string str) {
                int data = 0;
                int maxDivisor = std::numeric_limits<int>::max();
                size_t vSize = value.size();
                data = validStringToInt(str);
                auto calcArea = [](int divisor, int remains, double initial, const geometry::Polygon& elem) {
                    double rez = initial;
                    return rez + (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1 ? elem.area() : 0);
                    };

                if (data == -1) {
                    if (str == "EVEN") {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                            std::bind(calcArea, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "ODD") {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                            std::bind(calcArea, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "MEAN" && value.size() != 0) {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                            std::bind(calcArea, 2, -1, std::placeholders::_1, std::placeholders::_2)) / vSize << "\n";
                    }
                    else {
                        throw I_C;
                    }
                }
                else if (data > 2) {
                    std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                        std::bind(calcArea, maxDivisor, data, std::placeholders::_1, std::placeholders::_2)) << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void max(std::vector<geometry::Polygon>& value, const std::string str) {
                if (value.empty())
                    throw I_C;
                if (str == "AREA") {
                    auto maxArea = *std::max_element(value.begin(), value.end(),
                        [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                            return p1.area() < p2.area();
                        });
                    std::cout << std::fixed << std::setprecision(1) << maxArea.area() << "\n";
                }
                else if (str == "VERTEXES") {
                    auto maxVertexes = *std::max_element(value.begin(), value.end(),
                        [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                            return p1.points.size() < p2.points.size();
                        });
                    std::cout << maxVertexes.points.size() << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void min(std::vector<geometry::Polygon>& value, const std::string str) {
                if (value.empty())
                    throw I_C;
                if (str == "AREA") {
                    auto minArea = *std::min_element(value.begin(), value.end(),
                        [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                            return p1.area() < p2.area();
                        });
                    std::cout << std::fixed << std::setprecision(1) << minArea.area() << "\n";
                }
                else if (str == "VERTEXES") {
                    auto minVertexes = *std::min_element(value.begin(), value.end(),
                        [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                            return p1.points.size() < p2.points.size();
                        });
                    std::cout << minVertexes.points.size() << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void count(std::vector<geometry::Polygon>& value, const std::string str) {
                int data = 0;
                int maxDivisor = std::numeric_limits<int>::max();
                data = validStringToInt(str);
                auto calcConcur = [](int divisor, int remains, size_t initial, const geometry::Polygon& elem) {
                    return initial + (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1 ? 1 : 0);
                    };
                if (data == -1) {
                    if (str == "EVEN") {
                        std::cout << std::accumulate(value.begin(), value.end(), static_cast<size_t>(0),
                            std::bind(calcConcur, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "ODD") {
                        std::cout << std::accumulate(value.begin(), value.end(), static_cast<size_t>(0),
                            std::bind(calcConcur, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "ALL") {
                        std::cout << value.size() << "\n";
                    }
                    else {
                        throw I_C;
                    }
                }
                else if (data > 2) {
                    std::cout << std::accumulate(value.begin(), value.end(), static_cast<size_t>(0),
                        std::bind(calcConcur, maxDivisor, data, std::placeholders::_1, std::placeholders::_2)) << "\n";
                }
                else {
                    throw I_C;
                }
            }

            void filter(std::vector<geometry::Polygon>& value, const std::string str) {
                int data = 0;
                int maxDivisor = std::numeric_limits<int>::max();
                data = validStringToInt(str);
                auto filterElems = [](int divisor, int remains, std::vector<geometry::Polygon>& storage, const geometry::Polygon& elem) {
                    if (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1) {
                        storage.push_back(elem);
                    }
                    };

                std::vector<geometry::Polygon> filtered;
                if (data == -1) {
                    if (str == "EVEN") {
                        std::for_each(value.begin(), value.end(),
                            std::bind(filterElems, 2, 0, std::ref(filtered), std::placeholders::_1));
                    }
                    else if (str == "ODD") {
                        std::for_each(value.begin(), value.end(),
                            std::bind(filterElems, 2, 1, std::ref(filtered), std::placeholders::_1));
                    }
                    else {
                        throw I_C;
                    }
                }
                else if (data > 2) {
                    std::for_each(value.begin(), value.end(),
                        std::bind(filterElems, maxDivisor, data, std::ref(filtered), std::placeholders::_1));
                }
                else {
                    throw I_C;
                }

                std::swap(filtered, value);
            }

            void sort(std::vector<geometry::Polygon>& value, const std::string str) {
                if (str == "AREA") {
                    std::sort(value.begin(), value.end(), [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                        return p1.area() < p2.area();
                        });
                }
                else if (str == "VERTEXES") {
                    std::sort(value.begin(), value.end(), [](const geometry::Polygon& p1, const geometry::Polygon& p2) {
                        return p1.points.size() < p2.points.size();
                        });
                }
                else {
                    throw I_C;
                }
            }

            void reverse(std::vector<geometry::Polygon>& value, const std::string) {
                std::reverse(value.begin(), value.end());
            }

            void load(std::vector<geometry::Polygon>& value, const std::string filename) {
                std::ifstream input(filename);
                if (!input.is_open()) {
                    std::cout << "Error: could not open file\n";
                    return;
                }
                std::vector<geometry::Polygon> data;
                geometry::Polygon temp;
                while (input >> temp) {
                    data.push_back(temp);
                }
                std::swap(data, value);
            }

            void save(std::vector<geometry::Polygon>& value, const std::string filename) {
                std::ofstream output(filename);
                if (!output.is_open()) {
                    std::cout << "Error: could not open file\n";
                    return;
                }
                for (const auto& elem : value) {
                    output << elem << "\n";
                }
            }
        }


        int main() {
            std::vector<geometry::Polygon> polygons;
            std::string line, command, argument;
            std::istringstream iss;

            while (std::getline(std::cin, line)) {
                iss.clear();
                iss.str(line);
                iss >> command >> std::ws;
                std::getline(iss, argument);

                try {
                    if (command == "AREA") {
                        cmd::area(polygons, argument);
                    }
                    else if (command == "MAX") {
                        cmd::max(polygons, argument);
                    }
                    else if (command == "MIN") {
                        cmd::min(polygons, argument);
                    }
                    else if (command == "COUNT") {
                        cmd::count(polygons, argument);
                    }
                    else if (command == "FILTER") {
                        cmd::filter(polygons, argument);
                    }
                    else if (command == "SORT") {
                        cmd::sort(polygons, argument);
                    }
                    else if (command == "REVERSE") {
                        cmd::reverse(polygons, argument);
                    }
                    else if (command == "LOAD") {
                        cmd::load(polygons, argument);
                    }
                    else if (command == "SAVE") {
                        cmd::save(polygons, argument);
                    }
                    else {
                        std::cout << cmd::I_C << "\n";
                    }
                }
                catch (const std::string& errMsg) {
                    std::cout << errMsg << "\n";
                }
            }

            return 0;
        }
