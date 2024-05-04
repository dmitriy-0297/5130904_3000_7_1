#include "namespace.h"

using golikov::DataStruct;

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

    //Сортировка вектора
    std::sort(std::begin(data), std::end(data), golikov::compareDataStruct);

    //Вывод вектора с отсортированой информацией
    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
