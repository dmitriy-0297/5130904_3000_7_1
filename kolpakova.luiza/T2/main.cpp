#include "namespace.h"

using kolpakova::DataStruct;

int main()
{
  try
  {
    setlocale(LC_ALL, "rus");

    std::string input = "";
    std::vector< kolpakova::DataStruct > data;
    while (std::getline(std::cin, input)) {
      std::istringstream iss(input);
      kolpakova::DataStruct tmp;
      if (iss >> tmp) {
        data.push_back(tmp);
      }
    }
    std::sort(data.begin(), data.end(), kolpakova::compareDataStruct);

    std::copy(data.begin(), data.end(), std::ostream_iterator< kolpakova::DataStruct >(std::cout, "\n"));
  }
  catch (const std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
