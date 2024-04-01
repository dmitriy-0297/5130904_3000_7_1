#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>
#include <string>
struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
    DataStruct() : key1(0), key2(0), key3("") {}
};
std::istream& operator>>(std::istream& is, DataStruct& ds);
std::ostream& operator<<(std::ostream& os, const DataStruct& ds);
bool compareDataStructs(const DataStruct& a, const DataStruct& b);
#endif