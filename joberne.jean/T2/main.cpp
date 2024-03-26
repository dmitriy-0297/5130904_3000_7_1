#include "DataStruct.h"
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<DataStruct> data;

    // Чтение данных в вектор
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(data)
    );

    // Сортировка данных
    std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1.real() != b.key1.real()) return a.key1.real() < b.key1.real();
        if (a.key2.first != b.key2.first) return a.key2.first < b.key2.first;
        return a.key3.length() < b.key3.length();
    });

    // Вывод данных
    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
