#ifndef IO_FORMAT_GUARD_H
#define IO_FORMAT_GUARD_H

#include <iostream>

class IoFormatGuard {
public:
  IoFormatGuard(std::basic_ios<char>& s);
  ~IoFormatGuard();
private:
  std::basic_ios<char>& s_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios<char>::fmtflags fmt_;
};

#endif // IO_FORMAT_GUARD_H
