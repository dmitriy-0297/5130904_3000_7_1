#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "Polygon.h"
#include "Command.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Misapplication\nUsage: program_name <filename>\n";
        return EXIT_FAILURE;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: file didn't open\n";
        return EXIT_FAILURE;
    }

    std::vector<jean::Polygon> polygons;
    std::copy(std::istream_iterator<jean::Polygon>(file), std::istream_iterator<jean::Polygon>(), std::back_inserter(polygons));

    try {
        for (std::string line; std::getline(std::cin, line); ) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string cmd, param;
            iss >> cmd >> param;

            try {
                if (cmd == "AREA") cmd::area(polygons, param);
                else if (cmd == "MAX") cmd::max(polygons, param);
                else if (cmd == "MIN") cmd::min(polygons, param);
                else if (cmd == "COUNT") cmd::count(polygons, param);
                else if (cmd == "LESSAREA") cmd::lessArea(polygons);
                else if (cmd == "MAXSEQ") cmd::maxSeq(polygons);
                else throw cmd::I_C;
            } catch (const std::string &err) {
                std::cout << err << "\n";
            }
        }
    } catch (...) {
        std::cerr << "Wrong: Something went wrong\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

