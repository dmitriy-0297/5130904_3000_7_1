#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <string>

namespace abrosimov
{
    struct DataStruct
    {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct ULongLiteralIO
    {
        unsigned long long& ref;
    };

    struct ULongBinaryLiteralIO
    {
        unsigned long long& ref;
    };

    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, ULongLiteralIO&& dest);
    std::istream& operator>>(std::istream& in, ULongBinaryLiteralIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}
#endif

