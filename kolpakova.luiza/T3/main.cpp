#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "functions.h"

using namespace kolpakova;

int main(int argC, char* argV[])
{
  if (argC != 2) 
  {
    std::cerr << "Error: incorrect filename!" << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argV[1];

  std::ifstream in(fileName);

  if (!in)
  {
    std::cerr << "File not found!" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Polygon> data;

  while (!in.eof())
  {
    std::copy(std::istream_iterator<Polygon>(in),
      std::istream_iterator<Polygon>(),
      std::back_inserter(data));
    if (!in.eof() && in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  try
  {
    while (!std::cin.eof())
    {
      std::string command;

      std::cin >> command;

      try
      {
        if (command == "AREA")
          command::area(data);

        else if (command == "MIN")
          command::min(data);

        else if (command == "MAX")
          command::max(data);

        else if (command == "COUNT")
          command::count(data);

        else if (command == "RMECHO")
          command::rmecho(data);

        else if (command == "INTERSECTIONS")
          command::intersections(data);
        else if (command != "")

          throw "<INVALID COMMAND>";
      }
      catch (const char* error)
      {
        std::cout << error << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << "Error: Something wrong." << std::endl;
    return EXIT_FAILURE;
  }
}
