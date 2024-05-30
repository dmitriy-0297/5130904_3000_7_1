#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H

#include <iostream>

class Iofmtguard
{
public:
  Iofmtguard(std::basic_ios< char >& s);
  ~Iofmtguard();
private:
  std::basic_ios< char >& s_;
  char fill_;
  std::streamsize precision_;
  std::basic_ios< char >::fmtflags fmt_;
};


#endif
