#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "DataStruct.h"

int main()
{
    try
    {
        std::string input = "";
        std::vector<jean::DataStruct> data;

        while (std::getline(std::cin, input))
        {
            std::istringstream iss(input);
            jean::DataStruct tmp;
            if (iss >> tmp)
            {
                data.push_back(tmp);
            }
        }

        std::sort(std::begin(data), std::end(data));

        std::copy(std::begin(data), std::end(data), std::ostream_iterator<jean::DataStruct>(std::cout, "\n"));
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
