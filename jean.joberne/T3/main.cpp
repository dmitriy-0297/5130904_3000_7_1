#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

#include "geometry.h"
#include "io.h"
#include "functors.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
        return EXIT_FAILURE;
    }
    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error: file didn't open\n";
        return EXIT_FAILURE;
    }

    std::cout << std::setprecision(1) << std::fixed;
    std::vector<jean::Polygon> vec;
    std::copy(std::istream_iterator<jean::Polygon>(file),
              std::istream_iterator<jean::Polygon>(),
              std::back_inserter(vec));

    if (!file.eof() && file.fail())
    {
        file.clear();
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (!std::cin.eof())
    {
        std::cin.clear();
        std::string command;
        std::cin >> command;
        try
        {
            if (command == "AREA")
                functors::getTotalArea(vec);
            else if (command == "MIN")
                functors::getMin(vec);
            else if (command == "MAX")
                functors::getMax(vec);
            else if (command == "COUNT")
                functors::getQuantity(vec);
            else if (command == "LESSAREA")
                functors::lessArea(vec);
            else if (command == "SAME")
                functors::same(vec);
            else if (command == "ECHO")
                functors::echo(vec);
            else if (!std::cin.eof())
            {
                throw std::runtime_error("<INVALID COMMAND>");
            }
        }
        catch (std::exception &ex)
        {
            std::cout << ex.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

