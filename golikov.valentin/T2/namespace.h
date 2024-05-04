#ifndef NAMESPACE_H
#define NAMESPACE_H

#include "local.h"

namespace golikov
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  //struct for definition of complex type
  struct CMPDoubleIO
  {
    std::complex< double >& ref;
  };

  //struct for definition of ULL type
  struct ULLIO
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

  // scope guard для возврата состояния потока в первоначальное состояние
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
  std::istream& operator>>(std::istream& in, CMPDoubleIO&& dest);
  std::istream& operator>>(std::istream& in, ULLIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

  bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}


#endif
