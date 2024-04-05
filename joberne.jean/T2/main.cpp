#include "namespace.h"
using namespace jean;

int main() {
    try {
        std::vector<DataStruct> data;
        DataStruct tmp;
        while (std::cin >> tmp) {
            data.push_back(tmp);
        }

        std::sort(data.begin(), data.end(), compareDataStruct);

        for (const auto& item : data) {
            std::cout << item << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

