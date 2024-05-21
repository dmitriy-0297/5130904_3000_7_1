#include <fstream>
#include <map>

#include "polygonCommands.h"

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

  std::vector< Polygon > polygons;

  while (!inputF.eof())//inputF
  {
    std::copy(
      std::istream_iterator<Polygon>(inputF),
      std::istream_iterator<Polygon>(),
      std::back_inserter(polygons)
    );
    if (inputF.fail() && !inputF.eof())
    {
      inputF.clear();
      inputF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//
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
        perms(polygons);
      }
      else if (command == "RIGHTSHAPES")
      {
        rightShapes(polygons);
      }
      else if (command == "AREA")
      {
        area(polygons);
      }
      else if (command == "MAX")
      {
        max(polygons);
      }
      else if (command == "MIN")
      {
        min(polygons);
      }
      else if (command == "COUNT")
      {
        count(polygons);
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
