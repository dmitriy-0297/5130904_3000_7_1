#include <iomanip>
#include <iostream>
#include <string>
#include <limits>
#include "DataStruct.h"

namespace deleske {

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string del;
  size_t tSize = dest.delimiter.length();
  in >> std::setw(tSize) >> del;
  if (!in)
  {
    return in;
  }
  if (dest.delimiter != del)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, UllIO&& dest)
{
  std::istream::sentry sentry(in);
  ResPars rGard(in);
  if (!sentry)
  {
    return in;
  }
  if (!(in >> std::oct >> dest.ref))
  {
    return in;
  }
  return in;
}

std::istream& operator>>(std::istream& in, ComplexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string del;
  double real, imag;
  if (!(in >> DelimiterIO{"#c("}))
  {
    return in;
  }
  if (!(in >> real >> imag))
  {
    return in;
  }
  if (!(in >> DelimiterIO{")"}))
  {
    return in;
  }
  dest.ref = std::complex<double>(real, imag);
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{"\""}, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  in >> DelimiterIO{"(:"};
  if (!in)
  {
    return in;
  }

  for (int i = 0; i < 3; i++)
  {
    std::string key;
    if (!(in >> key))
    {
      return in;
    }

    if (key == "key1")
    {
      if (!(in >> UllIO{ dest.key1 }))
      {
        return in;
      }
    }
    else if (key == "key2")
    {
      if (!(in >> ComplexIO{ dest.key2 }))
      {
        return in;
      }
    }
    else if (key == "key3")
    {
      if (!(in >> StringIO{ dest.key3 }))
      {
        return in;
      }
    }
    else
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> DelimiterIO{":"};
    if (!in)
    {
      return in;
    }
  }
  in >> DelimiterIO{")"};

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  ResPars rGard(out);

  out << "(:key1 " << "0" << std::oct << dest.key1 <<
        ":key2 " << "#c(" << std::fixed << std::setprecision(1) << dest.key2.real() << " " <<
        std::fixed << std::setprecision(1) << dest.key2.imag() << ")" <<
        ":key3 \"" << dest.key3 << "\":)";
  return out;
}

ResPars::ResPars(std::basic_ios<char>& strm) :
  strm_(strm),
  fill_(strm.fill()),
  precision_(strm.precision()),
  fmtFlags_(strm.flags())
{}

ResPars::~ResPars()
{
  strm_.fill(fill_);
  strm_.precision(precision_);
  strm_.flags(fmtFlags_);
}

}

