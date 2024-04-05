#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <complex>
#include <utility>
#include <string>

namespace jean {
    struct DataStruct {
        char key1; // CHR LIT
        std::pair<long long, unsigned long long> key2; // RAT LSP
        std::string key3;
    };

    struct CharLiteralIO {
        char& ref;
    };

    struct RationalLiteralIO {
        std::pair<long long, unsigned long long>& ref;
    };

    class iofmtguard {
    public:
        iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, CharLiteralIO&& dest);
    std::istream& operator>>(std::istream& in, RationalLiteralIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& src);

    bool compareDataStruct(const DataStruct& a, const DataStruct& b);
}

#endif
