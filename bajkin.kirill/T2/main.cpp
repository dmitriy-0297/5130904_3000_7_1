#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "dataStruct.h"

const std::string ERROR_PUSH = "Ошибка ввода в массив";

int main()
{
  using bajkin::DataStruct;
  using bajkin::compareVector;
  std::vector<DataStruct> data;

  std::string line = "";

  while (std::getline(std::cin, line))
  {
    std::istringstream iss1(line);
    DataStruct current;
    if (iss1 >> current)
    {
      try {
        data.push_back(current);
      }
      catch (...) {
        std::cerr << ERROR_PUSH;
        return EXIT_FAILURE;
      }
    }
  }

  std::sort(data.begin(), data.end(), compareVector);

  std::copy(std::begin(data), std::end(data), std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
