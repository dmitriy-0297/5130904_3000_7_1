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

        namespace Command {

            void area(const std::vector<Geometry::Polygon>& polygons) {
                double totalArea = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [](double sum, const Geometry::Polygon& polygon) {
                        return sum + polygon.area();
                    });

                std::cout << "Total Area: " << std::fixed << std::setprecision(1) << totalArea << std::endl;
            }

            void maxArea(const std::vector<Geometry::Polygon>& polygons) {
                auto it = std::max_element(polygons.begin(), polygons.end(),
                    [](const Geometry::Polygon& a, const Geometry::Polygon& b) {
                        return a.area() < b.area();
                    });

                if (it != polygons.end()) {
                    std::cout << "Max Area: " << std::fixed << std::setprecision(1) << it->area() << std::endl;
                }
            }

            void minArea(const std::vector<Geometry::Polygon>& polygons) {
                auto it = std::min_element(polygons.begin(), polygons.end(),
                    [](const Geometry::Polygon& a, const Geometry::Polygon& b) {
                        return a.area() < b.area();
                    });

                if (it != polygons.end()) {
                    std::cout << "Min Area: " << std::fixed << std::setprecision(1) << it->area() << std::endl;
                }
            }
        }
        #endif
