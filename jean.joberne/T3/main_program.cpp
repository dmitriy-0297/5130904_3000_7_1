#include <fstream>
#include <map>
#include <stdexcept>
#include <iostream>
#include "shape_commands.h"

const int ERROR_CODE = 1;

void readShapesFromFile(const std::string& filename, std::vector<Shape>& shapes)
{
  std::ifstream inputFile(filename);
  if (!inputFile)
  {
    throw std::runtime_error("Error: Could not open the input file.");
  }

  while (!inputFile.eof())
  {
    std::copy(
      std::istream_iterator<Shape>(inputFile),
      std::istream_iterator<Shape>(),
      std::back_inserter(shapes)
    );
    if (inputFile.fail() && !inputFile.eof())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  inputFile.close();
}

int main(int argc, char** argv)
{
  try
  {
    if (argc < 2)
    {
      throw std::runtime_error("Error: No input file provided.");
    }

    std::vector<Shape> shapes;
    readShapesFromFile(argv[1], shapes);

    std::cin.clear();

    std::string command;
    while (!std::cin.eof())
    {
      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

      try
      {
        std::cin >> command;
        if (std::cin.eof())
        {
          break;
        }
        if (command == "PERMS")
        {
          perms(shapes);
        }
        else if (command == "AREA")
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
        else
        {
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::invalid_argument("<INVALID COMMAND>");
        }
      }
      catch (const std::exception& e)
      {
        std::cout << e.what() << '\n';
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return ERROR_CODE;
  }

  return 0;
}
