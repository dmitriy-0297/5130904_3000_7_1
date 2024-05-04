#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_

#include <iostream>
#include <vector>
#include <complex>

namespace deleske {

struct DataStruct
{
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
};

struct UllIO
{
    unsigned long long &ref;
};

struct ComplexIO
{
    std::complex<double> &ref;
};

struct StringIO
{
    std::string &ref;
};

struct DelimiterIO
{
    std::string delimiter;
};

class ResPars
{
public:
    ResPars(std::basic_ios<char> &strm);
    ~ResPars();

private:
    std::basic_ios<char> &strm_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmtFlags_;
};

std::istream& operator>>(std::istream &in, DelimiterIO&& dest);
std::istream& operator>>(std::istream &in, UllIO &dest);
std::istream& operator>>(std::istream &in, ComplexIO &dest);
std::istream& operator>>(std::istream &in, StringIO &dest);
std::istream& operator>>(std::istream &in, DataStruct &dest);
std::ostream& operator<<(std::ostream &out, const DataStruct &dest);

}

#endif



