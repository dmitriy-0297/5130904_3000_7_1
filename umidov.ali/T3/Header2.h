        #ifndef COMMAND_H
        #define COMMAND_H
        #include "Header1.h"
        #include <iostream>
        #include <vector>
        #include <algorithm>
        #include <numeric>
        #include <limits>
        #include <functional>
        #include <iomanip>
        #include <map>
        namespace Command {

            void processCommand(const std::string& cmd, const std::vector<Geometry::Polygon>& polygons) {
                if (cmd == "total_area") {
                    double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                        [](double sum, const Geometry::Polygon& polygon) {
                            return sum + polygon.area();
                        });
                    std::cout << "Total Area: " << std::fixed << std::setprecision(1) << totalArea << std::endl;
                }
                else if (cmd == "max_area") {
                    auto it = std::max_element(polygons.begin(), polygons.end(),
                        [](const Geometry::Polygon& a, const Geometry::Polygon& b) {
                            return a.area() < b.area();
                        });
                    if (it != polygons.end()) {
                        std::cout << "Max Area: " << std::fixed << std::setprecision(1) << it->area() << std::endl;
                    }
                }
                else if (cmd == "min_area") {
                    auto it = std::min_element(polygons.begin(), polygons.end(),
                        [](const Geometry::Polygon& a, const Geometry::Polygon& b) {
                            return a.area() < b.area();
                        });
                    if (it != polygons.end()) {
                        std::cout << "Min Area: " << std::fixed << std::setprecision(1) << it->area() << std::endl;
                    }
                }
                else if (cmd == "list_polygons") {
                    for (const auto& polygon : polygons) {
                        std::cout << "Polygon with " << polygon.points.size() << " vertices." << std::endl;
                    }
                }
                else if (cmd == "count_polygons") {
                    std::cout << "Number of polygons: " << polygons.size() << std::endl;
                }
                else {
                    std::cout << "Invalid command." << std::endl;
                }
            }

        }
        #endif
