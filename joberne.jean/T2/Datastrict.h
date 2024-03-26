#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <complex>
#include <utility>
#include <string>
#include <sstream>

struct DataStruct {
    std::complex<double> key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;

    // Перегрузка оператора >> для чтения данных в структуру
    friend std::istream& operator>>(std::istream& is, DataStruct& ds) {
        std::string line;
        if (std::getline(is, line)) {
            std::istringstream iss(line);
            char check1, check2, delim;
            double real, imag;
            long long num;
            unsigned long long den;
            std::string data;
            if (iss >> check1 >> std::noskipws >> delim >> std::skipws >> real >> imag >> num >> den >> std::quoted(data) >> check2 && check1 == '(' && check2 == ')' && delim == ',') {
                ds.key1 = {real, imag};
                ds.key2 = {num, den};
                ds.key3 = data;
            } else {
                // Сброс флагов ошибок для избежания влияния на последующие операции чтения
                is.clear(std::ios::failbit);
            }
        }
        return is;
    }

    // Перегрузка оператора << для вывода данных структуры
    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
        os << "(" << ds.key1.real() << ", " << ds.key1.imag() << ", " << ds.key2.first << ", " << ds.key2.second << ", \"" << ds.key3 << "\")";
        return os;
    }
};

#endif // DATASTRUCT_H
