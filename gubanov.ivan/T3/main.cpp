#include "command.h"

int main(int argc, char* argv[])
{
  using namespace gubanov;
  using namespace command;
  if (argc != 2)
  {
    std::cerr << "Error: filename missing\n";
    return EXIT_FAILURE;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "Error: file doesn't exists\n";
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<Polygon> fileData;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<Polygon>(file),
      std::istream_iterator<Polygon>(),
      std::back_inserter(fileData));

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
        getTotalArea(fileData);
      }
      else if (command == "MAX" || command == "MIN")
      {
        calculateMinOrMax(fileData, command);
      }
      else if (command == "COUNT")
      {
        countPolygons(fileData);
      }
      else if (command == "INFRAME")
      {
        InFrame(fileData);
      }
      else if (command == "ECHO")
      {
        echo(fileData);
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
