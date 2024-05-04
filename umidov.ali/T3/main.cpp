    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <string>
    #include <sstream>
    #include <algorithm>
    #include <functional>
    #include <iomanip>
    #include <cmath>

    struct Point {
        int x;
        int y;
    };

    struct Polygon {
        std::vector<Point> points;

        double area() const {
            double totalArea = 0.0;
            for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
                totalArea += (points[j].x + points[i].x) * (points[j].y - points[i].y);
            }
            return std::abs(totalArea / 2.0);
        }
    };

    std::istream& operator>>(std::istream& is, Point& point) {
        char delim1, delim2, delim3;
        if (!(is >> delim1 >> point.x >> delim2 >> point.y >> delim3)) {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

    std::istream& operator>>(std::istream& is, Polygon& poly) {
        size_t numVertices;
        is >> numVertices;
        poly.points.resize(numVertices);
        for (Point& point : poly.points) {
            is >> point;
        }
        return is;
    }

    void processAreaCommand(
        const std::vector<Polygon>& polygons,
        const std::string& criteria
    ) {
        double totalArea = 0.0;
        int count = 0;
        for (const auto& poly : polygons) {
            if ((criteria == "ODD" && (poly.points.size() % 2 != 0)) ||
                (criteria == "EVEN" && (poly.points.size() % 2 == 0)) ||
                (criteria == "MEAN")) {
                totalArea += poly.area();
                if (criteria == "MEAN") {
                    count++;
                }
            }
        }
        if (criteria == "MEAN" && count > 0) {
            totalArea /= count;
        }
        std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
    }

    void processCountCommand(
        const std::vector<Polygon>& polygons,
        const std::string& criteria
    ) {
        int count = std::count_if(
            polygons.begin(), polygons.end(),
            [criteria](const Polygon& poly) {
                return (criteria == "ODD" && (poly.points.size() % 2 != 0)) ||
                    (criteria == "EVEN" && (poly.points.size() % 2 == 0));
            }
        );
        std::cout << count << std::endl;
    }

    int main(int argc, char* argv[]) {
        if (argc != 2) {
            std::cerr << "Usage: " << argv[0] << " <filename>\n";
            return 1;
        }

        std::ifstream inFile(argv[1]);
        if (!inFile) {
            std::cerr << "Error opening file: " << argv[1] << std::endl;
            return 1;
        }

        std::vector<Polygon> polygons;
        Polygon poly;
        while (inFile >> poly) {
            polygons.push_back(poly);
        }

        std::string command;
        while (std::cin >> command) {
            if (command == "AREA") {
                std::string type;
                std::cin >> type;
                processAreaCommand(polygons, type);
            }
            else if (command == "COUNT") {
                std::string type;
                std::cin >> type;
                processCountCommand(polygons, type);
            }
            else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }

        return 0;
    }
