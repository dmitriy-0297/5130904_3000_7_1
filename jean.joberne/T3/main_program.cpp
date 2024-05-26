#include <fstream>
#include <map>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>
#include <string>
#include <iomanip>
#include "shape_commands.h"

using namespace jean;
using namespace methods;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error (incorrect filename)\n";
    return EXIT_FAILURE;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "Error: (file not exist)\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Shape> shapes;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<Shape>(file),
      std::istream_iterator<Shape>(),
      std::back_inserter(shapes));

    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      if (command == "AREA")
      {
        area(shapes);
      }
      else if (command == "MAX")
      {
        max(shapes);
      }
      else if (command == "MIN")
      {
        min(shapes);
      }
      else if (command == "COUNT")
      {
        count(shapes);
      }
      else if (command == "LESSAREA")
      {
        lessArea(shapes);
      }
      else if (command == "MAXSEQ")
      {
        maxseq(shapes);
      }
      else if (command != "")
      {
        throw "<INVALID COMMAND>";
      }
    }
    catch (const char* error)
    {
      std::cout << error << std::endl;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  return EXIT_SUCCESS;
}
