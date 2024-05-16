        #ifndef GEOMETRY_H
        #define GEOMETRY_H

        #include <vector>
        #include <cmath>

        namespace Geometry {

            struct Point {
                int x, y;

                Point(int x = 0, int y = 0) : x(x), y(y) {}
            };

            struct Polygon {
                std::vector<Point> points;

                double area() const {
                    double area = 0.0;
                    int n = points.size();
                    for (int i = 0; i < n; i++) {
                        int j = (i + 1) % n;
                        area += points[i].x * points[j].y;
                        area -= points[j].x * points[i].y;
                    }
                    return std::abs(area / 2.0);
                }
            };

        }

        #endif
