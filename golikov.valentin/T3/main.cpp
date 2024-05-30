#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "command.h"

const std::string I_C = "<INVALID COMMAND>";
const std::string INCORRECT_USAGE = "Incorrect usage!";
const std::string NO_SUCH_FILE = "File not found!";
const std::string ERROR = "Something goes wrong";

using namespace golikov;

int main(int argC, char* argV[])
{
  if (argC != 2)
  {
    std::cerr << INCORRECT_USAGE << std::endl;
    return EXIT_FAILURE;
  }

  std::string fileName = argV[1];

  std::ifstream file(fileName);

  if (!file)
  {
    std::cerr << NO_SUCH_FILE << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Polygon> data;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<Polygon>(file),
      std::istream_iterator<Polygon>(),
      std::back_inserter(data));
    if (!file.eof() && file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  try
  {
    while (!std::cin.eof())
    {
      std::string cmd;

      std::cin >> cmd;

      try
      {
        if (cmd == "AREA")
          commands::getFullArea(data);
        else if (cmd == "MIN")
          commands::getMin(data);
        else if (cmd == "MAX")
          commands::getMax(data);
        else if (cmd == "COUNT")
          commands::countFigures(data);
        else if (cmd == "RMECHO")
          commands::lessarea(data);
        else if (cmd == "INTERSECTIONS")
          commands::intersections(data);
        else if (cmd != "")
          throw I_C;
      }
      catch (const std::string &err)
      {
        std::cout << err << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }

    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << ERROR << std::endl;
    return EXIT_FAILURE;
  }
}
