#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <iterator>
#include "DataStruct.h"

using namespace deleske;

int main() {
  try {
    std::vector<DataStruct> ds_original;
    std::string request;
    while (std::getline(std::cin, request)) {
      std::istringstream iss(request);
      DataStruct temp;
      if (iss >> temp) {
        ds_original.push_back(temp);
      }
    }

    std::sort(ds_original.begin(), ds_original.end(), [](const DataStruct &ds1, const DataStruct &ds2) {
      if (ds1.key1 != ds2.key1) return ds1.key1 < ds2.key1;

      if (std::abs(ds1.key2) != std::abs(ds2.key2)) {
        return std::abs(ds1.key2) < std::abs(ds2.key2);
      } else {
        return ds1.key3.length() < ds2.key3.length();
      }
    });

    std::copy(ds_original.begin(), ds_original.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  } catch (std::exception &er) {
    std::cerr << er.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

