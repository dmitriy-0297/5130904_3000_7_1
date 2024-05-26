#include <fstream>
#include <map>
#include "shape_commands.h"

int main(int nArguments, char** file)
{
  if (nArguments < 2)
  {
    return 1;
  }

  std::ifstream inputF(file[1]);
  if (!inputF)
  {
    return 1;
  }

  std::vector< Shape > shapes;

  while (!inputF.eof())
  {
    std::copy(
      std::istream_iterator<Shape>(inputF),
      std::istream_iterator<Shape>(),
      std::back_inserter(shapes)
    );
    if (inputF.fail() && !inputF.eof())
    {
      inputF.clear();
      inputF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

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
        throw std::invalid_argument("");
      }
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }

  return 0;
}
