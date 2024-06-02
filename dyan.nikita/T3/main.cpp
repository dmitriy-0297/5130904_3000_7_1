#include "local.h"
#include "shape.h"
#include "command.h"

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
const std::string INCORRECT_USAGE = "Incorrect usage";
const std::string NO_SUCH_FILE = "File not found";
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
    std::cerr << NO_SUCH_FILE << std::endl;
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
          std::string arg = "";
          std::cin >> arg;
          command::area(data, arg);
        }
        else if (cmd == "MAX")
        {
          std::string arg = "";
          std::cin >> arg;
          command::max(data, arg);
        }
        else if (cmd == "MIN")
        {
          std::string arg = "";
          std::cin >> arg;
          command::min(data, arg);
        }
        else if (cmd == "COUNT")
        {
          std::string arg = "";
          std::cin >> arg;
          command::count(data, arg);
        }
        else if (cmd == "RMECHO")
        {
          command::rmecho(data);
        }
        else if (cmd == "SAME")
        {
          dyan::Polygon arg;
          std::cin >> arg;
          command::same(data, arg);
        }
        else if (cmd != "")
        {
          throw std::invalid_argument(INVALID_COMMAND);
        }
      }
      catch (const std::invalid_argument& er)
      {
        std::cout << er.what() << std::endl;
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
