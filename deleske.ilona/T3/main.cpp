#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <iomanip>

#include "geometry.h"
#include "io.h"
#include "commands.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
    return EXIT_FAILURE;
  }
  std::string fileName = argv[1];
  std::ifstream file(fileName);
  if(!file)
  {
    std::cerr << "Error: file didn't open\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;
  std::vector<deleske::Polygon> vec;
  while (!file.eof())
  {
    std::copy(
        std::istream_iterator<deleske::Polygon>(file),
        std::istream_iterator<deleske::Polygon>(),
        std::back_inserter(vec)
    );
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  while (!std::cin.eof())
  {
    std::cin.clear();
    std::string command;
    std::cin >> command;
    try
    {
      if (command == "AREA")
        deleske::area(vec);
      else if (command == "MIN")
        deleske::min(vec);
      else if (command == "MAX")
        deleske::max(vec);
      else if (command == "COUNT")
        deleske::count(vec);
      else if (command == "ECHO")
        deleske::echo(vec);
      else if (command == "MAXSEQ")
        deleske::maxSeq(vec);
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
