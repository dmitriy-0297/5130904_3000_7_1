        #include "Header2.h"
        #include <fstream>
        #include <sstream>
        #include <string>

        int main(int argc, char** argv) {
            if (argc != 2) {
                std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
                return EXIT_FAILURE;
            }

            std::ifstream file(argv[1]);
            if (!file) {
                std::cerr << "Error opening file: " << argv[1] << std::endl;
                return EXIT_FAILURE;
            }

            std::vector<Geometry::Polygon> polygons;
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                int n;
                iss >> n;
                Geometry::Polygon poly;
                for (int i = 0; i < n; i++) {
                    int x, y;
                    char ch;
                    iss >> ch >> x >> ch >> y >> ch;
                    poly.points.push_back({ x, y });
                }
                polygons.push_back(poly);
            }

            Command::area(polygons);
            Command::maxArea(polygons);
            Command::minArea(polygons);

            return EXIT_SUCCESS;
        }
