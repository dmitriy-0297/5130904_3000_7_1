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

            void area(std::vector<geometry::Polygon>& polygons, const std::string str) {
                int data = 0;
                size_t vSize = polygons.size();
                data = validStringToInt(str);
                auto calcArea = [](int divisor, int remains, double initial, const geometry::Polygon& elem) {
                    double rez = initial;
                    return rez + (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1 ? elem.area() : 0);
                    };

                if (data == -1) {
                    if (str == "EVEN") {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            std::bind(calcArea, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "ODD") {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            std::bind(calcArea, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";
                    }
                    else if (str == "MEAN" && polygons.size() != 0) {
                        std::cout << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                            std::bind(calcArea, 2, -1, std::placeholders::_1, std::placeholders::_2)) / vSize << "\n";
                    }
                    else {
                        throw I_C;
                    }
                }
                else if (data > 2) {
                    std::cout << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        std::bind(calcArea, data, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
                }
                else {
                    throw I_C;
                }
            }
        }

        int main() {
            std::vector<geometry::Polygon> polygons;
            std::string command;
            while (std::getline(std::cin, command)) {
                try {
                    if (command == "EXIT")
                        break;
                    else if (command.find("AREA") == 0) {
                        std::istringstream iss(command);
                        std::string token;
                        iss >> token >> token;
                        cmd::area(polygons, token);
                    }
                }
                catch (...) {
                    std::cerr << cmd::I_C << "\n";
                }
            }
            return 0;
        }
