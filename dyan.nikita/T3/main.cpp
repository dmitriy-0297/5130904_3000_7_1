#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <limits>

#include "shape.h"
#include "command.h"

const std::string INVALID_COMMAND = "<INVALID_COMMAND>";
const std::string INCORRECT_USAGE = "Incorrect usage";
const std::string FILE_NOT_FOUND = "File not found";
const std::string UNEXPECTED_ERROR = "Something went wrong";

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << INCORRECT_USAGE << std::endl;
    return EXIT_FAILURE;
  }
  std::string filename = argv[1];
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << FILE_NOT_FOUND << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << std::setprecision(1) << std::fixed;
  std::vector<dyan::Polygon> data;
  using input_it_t = std::istream_iterator<dyan::Polygon>;
  while (!file.eof())
  {
    std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(data));
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
        {
          command::area(data);
        }
        else if (cmd == "MAX")
        {
          command::max(data);
        }
        else if (cmd == "MIN")
        {
          command::min(data);
        }
        else if (cmd == "COUNT")
        {
          command::count(data);
        }
        else if (cmd == "RMECHO")
        {
          command::rmecho(data);
        }
        else if (cmd == "SAME")
        {
          command::same(data);
        }
        else if (cmd != "")
        {
          throw INVALID_COMMAND;
        }
      }
      catch (const char* err)
      {
        std::cout << err << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    return EXIT_SUCCESS;
  }
  catch (...)
  {
    std::cerr << UNEXPECTED_ERROR << std::endl;
    return EXIT_FAILURE;
  }
}
