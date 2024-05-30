#include "io_format_guard.h"

Iofmtguard::Iofmtguard(std::basic_ios<char>& s)
  : s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags()) {}

Iofmtguard::~Iofmtguard() {
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
