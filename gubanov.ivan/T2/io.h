#ifndef IO_H
#define IO_H

#include <iostream>
#include <vector>
#include <sstream>

namespace gubanov
{
  struct DataStruct
  {
    double key1;
    char key2;
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

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios<char>& stream);
    ~StreamGuard();
  private:
    std::basic_ios<char>& stream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, DoubleIO&& dest);
  std::istream& operator>>(std::istream& in, CharIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  std::string doubleToScientific(double number);
}
#endif
