#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <cmath>
#include <exception>

namespace gruzdev
{
    struct DataStruct
    {
        unsigned long long key1;
        std::complex<double> key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct CMPDoubleIO
    {
        std::complex<double>& ref;
    };

    struct ULLLiteralIO
    {
        unsigned long long& ref;
    };

    struct ULLOctalIO
    {
        unsigned long long& ref;
    };

    struct DoubleIO
    {
        double& num;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct LabelIO
    {
        std::string exp;
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
    std::istream& operator>>(std::istream& in, CMPDoubleIO&& dest);
    std::istream& operator>>(std::istream& in, ULLLiteralIO&& dest);
    std::istream& operator>>(std::istream& in, ULLOctalIO&& dest);
    std::istream& operator>>(std::istream& in, DoubleIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
