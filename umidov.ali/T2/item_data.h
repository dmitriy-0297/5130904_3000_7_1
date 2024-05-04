#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <string>

namespace umidov {
    struct DataStruct {
        unsigned long long key1;
        unsigned long long key2;
        std::string key3;
    };

    struct DelimiterIO {
        char exp;
    };

    struct StringIO {
        std::string& ref;
    };

    struct LIT {
        unsigned long long& ref;
    };

    struct OCT {
        unsigned long long& ref;
    };

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& stream);

        ~iofmtguard();

    private:
        std::basic_ios<char>& stream_;
        char fill_;
        std::streamsize precision_;
        std::ios_base::fmtflags flags_;
    };

    std::istream& operator>>(std::istream& input, DelimiterIO&& destination);

    std::istream& operator>>(std::istream& input, LIT&& destination);

    std::istream& operator>>(std::istream& input, OCT&& destination);

    std::istream& operator>>(std::istream& input, StringIO&& destination);

    std::istream& operator>>(std::istream& input, DataStruct& destination);

    std::ostream& operator<<(std::ostream& output, const DataStruct& source);

    bool compareDataStruct(const DataStruct& first, const DataStruct& second);
}

#endif
