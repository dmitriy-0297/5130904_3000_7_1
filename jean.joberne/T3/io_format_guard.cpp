#include "io_format_guard.h"

IoFormatGuard::IoFormatGuard(std::basic_ios<char>& s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags()) {}

IoFormatGuard::~IoFormatGuard() {
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
