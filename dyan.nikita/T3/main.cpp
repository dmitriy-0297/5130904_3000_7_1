#include "local.h"
#include "shape.h"
#include "command.h"

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
const std::string INCORRECT_USAGE = "Incorrect usage";
const std::string FILE_NOT_FOUND = "File not found";
const std::string UNEXPECTED_ERROR = "Something went wrong";

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << INCORRECT_USAGE;
    return EXIT_FAILURE;
  }

  const std::string filename = argv[1];
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << FILE_NOT_FOUND;
    return EXIT_FAILURE;
  }

  std::cout << std::setprecision(1) << std::fixed;

  std::vector<dyan::Polygon> fileData;

  while (!file.eof())
  {
    std::copy(std::istream_iterator<dyan::Polygon>(file),
      std::istream_iterator<dyan::Polygon>(),
      std::back_inserter(fileData));

    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  while (!std::cin.eof())
  {
    std::string cmd;
    std::cin >> cmd;
    try
    {
      if (cmd == "AREA")
      {
        command::area(fileData);
      }
      else if (cmd == "MAX")
      {
        command::max(fileData);
      }
      else if (cmd == "MIN")
      {
        command::min(fileData);
      }
      else if (cmd == "COUNT")
      {
        command::count(fileData);
      }
      else if (cmd == "RMECHO")
      {
        command::rmecho(fileData);
      }
      else if (cmd == "SAME")
      {
        command::same(fileData);
      }
      else if (cmd != "")
      {
        throw INVALID_COMMAND;
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
