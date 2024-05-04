#ifndef IOFMT_GUARD_H
#define IOFMT_GUARD_H
#include<iostream>

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

iofmtguard::iofmtguard(std::basic_ios<char>& s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}
iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
#endif
