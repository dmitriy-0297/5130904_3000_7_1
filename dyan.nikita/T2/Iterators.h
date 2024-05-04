#ifndef ITERATORS_H
#define ITERATORS_H

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <iterator>
#include <vector>
#include <iomanip>

namespace dyan
{
  struct DataStruct
  {
    double key1 = 0.0;
    long long key2 = 0;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct SLLIO
  {
    long long& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, SLLIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

  bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
