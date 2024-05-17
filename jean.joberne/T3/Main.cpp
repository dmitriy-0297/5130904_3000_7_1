#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "Command.h"
#include "Polygon.h"

const std::string I_CMD = "<INVALID COMMAND>";

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Misapplication\n";
        std::cout << "Usage: program_name <filename>\n";
        return EXIT_FAILURE;
    }

    std::string fileName = argv[1];
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error: file didn't open\n";
        return EXIT_FAILURE;
    }

    std::vector<jean::Polygon> value;
    std::copy(std::istream_iterator<jean::Polygon>(file), std::istream_iterator<jean::Polygon>(), std::back_inserter(value));

    try {
        for(;;) {
            std::string str;
            if (!(std::getline(std::cin, str) && !str.empty() && !std::cin.eof())) {
                break;
            }

            std::istringstream iss(str); // Correctly using std::istringstream
            std::string comnd1, comnd2;
            iss >> comnd1 >> comnd2;

            try {
                if (comnd1 == "AREA") {
                    cmd::area(value, comnd2);
                } else if (comnd1 == "MAX") {
                    cmd::max(value, comnd2);
                } else if (comnd1 == "MIN") {
                    cmd::min(value, comnd2);
                } else if (comnd1 == "COUNT") {
                    cmd::count(value, comnd2);
                } else if (comnd1 == "MAXSEQ") {
                    cmd::maxSeq(value);
                } else if (comnd1 == "LESSAREA") {
                    cmd::lessArea(value);
                } else {
                    throw I_CMD;
                }
            } catch (const std::string& e) {
                std::cout << e << "\n";
            }
        }
        return EXIT_SUCCESS;
    } catch (...) {
        std::cerr << "Wrong: Something went wrong\n";
        return EXIT_FAILURE;
    }
}

