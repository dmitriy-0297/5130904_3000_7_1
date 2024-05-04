#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "io.h"

using namespace gubanov;

int main()
{
  std::vector<DataStruct> data;
  std::string line = "";

  while (std::getline(std::cin, line))
  {
    std::istringstream iss(line);
    DataStruct temp;
    if (iss >> temp)
    {
      data.push_back(temp);
    }
  }

  std::sort(std::begin(data), std::end(data),
    [](const DataStruct& data1, const DataStruct& data2)
    {
      if (data1.key1 == data2.key1)
      {
        if (data1.key2 == data2.key2)
          return data1.key3.length() < data2.key3.length();
        return data1.key2 < data2.key2;
      }
      return data1.key1 < data2.key1;
    }
  );

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator<DataStruct>(std::cout, "\n")
  );

  return EXIT_SUCCESS;
}
