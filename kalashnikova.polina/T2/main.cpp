#include "iterators.h"
#include <algorithm>

using kalashnikova::DataStruct;

int main()
{
  try
  {
    std::string input = "";
    std::vector< DataStruct > data;

    while (std::getline(std::cin, input))
    {
      std::istringstream iss(input);
      DataStruct temp;
      if (iss >> temp)
      {
        data.push_back(temp);
      }
    }

    std::sort(std::begin(data), std::end(data), kalashnikova::compareDataStruct);

    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
  }
  catch (std::exception& er)
  {
    std::cerr << er.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
