#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datastruct.h"
#include "item_data.h"

int main() {
    try {
        std::string input = "";
        std::vector<umidov::DataStruct> data;

        while (std::getline(std::cin, input)) {
            std::istringstream iss(input);
            umidov::DataStruct tmp;
            if (iss >> tmp) {
                data.push_back(tmp);
            }
        }

        std::sort(data.begin(), data.end(), umidov::compareDataStruct);

        std::copy(data.begin(), data.end(), std::ostream_iterator<umidov::DataStruct>(std::cout, "\n"));
    }
    catch (std::exception& ex) {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
