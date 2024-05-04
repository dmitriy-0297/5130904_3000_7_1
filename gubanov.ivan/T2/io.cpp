#include <string>
#include <iomanip>
#include "io.h"

gubanov::StreamGuard::StreamGuard(std::basic_ios<char>& stream) :
  stream_(stream),
  fill_(stream.fill()),
  precision_(stream.precision()),
  fmt_(stream.flags())
{}

gubanov::StreamGuard::~StreamGuard()
{
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(fmt_);
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char symbol = '0';
  in >> symbol;
  if (in && (symbol != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::DoubleIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::string input = "";
  in >> input;
  if ((input[1] == '.' && (input[4] == 'e' || input[4] == 'E')
    && (input[5] == '+' || input[5] == '-'))
    || (input[1] == '.' && (input[3] == 'e' || input[3] == 'E')
      && (input[4] == '+' || input[4] == '-')))
  {
    if (input[input.length() - 2] == ':')
    {
      in.putback(')');
      in.putback(':');
      input.erase(input.length() - 2, input.length());
      dest.ref = std::stod(input);
    }
    else
    {
      in.putback(*input.rbegin());
      in.putback('y');
      in.putback('e');
      in.putback('k');
      in.putback(':');
      input.erase(input.length() - 5, input.length());
      dest.ref = std::stod(input);
    }
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::CharIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char symbol;
  if (in >> DelimiterIO{ '\'' } >> symbol >> DelimiterIO{ '\'' })
  {
    dest.ref = symbol;
  }
  return in;
}

std::istream& gubanov::operator>>(std::istream& in, gubanov::StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}


std::istream& gubanov::operator>>(std::istream& in, gubanov::DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  DataStruct input;
  {
    using sep = DelimiterIO;
    using dbl = DoubleIO;
    using chr = CharIO;
    using str = StringIO;

    in >> sep{ '(' };
    bool flag1 = false, flag2 = false, flag3 = false;
    while (true)
    {
      if (flag1 && flag2 && flag3)
      {
        break;
      }
      std::string key;
      char symbol = '0';
      in >> symbol;
      if (!in)
      {
        break;
      }

      if (symbol == ':' && (in >> key))
      {
        if (key == "key1")
        {
          in >> dbl{ input.key1 };
          flag1 = true;
        }
        else if (key == "key2")
        {
          in >> chr{ input.key2 };
          flag2 = true;
        }
        else if (key == "key3")
        {
          in >> str{ input.key3 };
          flag3 = true;
        }
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::string gubanov::doubleToScientific(double number)
{
  std::stringstream ss;
  ss << std::scientific << number;
  std::string out = ss.str();
  size_t i = std::min(out.find('E'), out.find('e'));
  while (out[i - 1] == '0' && out[i - 2] != '.')
  {
    out.erase(i - 1, 1);
    i = std::min(out.find('E'), out.find('e'));
  }
  while (out[i + 2] == '0')
  {
    out.erase(i + 2, 1);
    i = std::min(out.find('E'), out.find('e'));
  }
  return out;
}

std::ostream& gubanov::operator<<(std::ostream& out, const gubanov::DataStruct& src)
{
  std::ostream::sentry sentry(out);

  if (!sentry)
  {
    return out;
  }

  StreamGuard fmtguard(out);
  out << "(";
  out << ":key1 " << doubleToScientific(src.key1);
  out << ":key2 " << "'" << src.key2 << "'";
  out << ":key3 " << "\"" << src.key3 << "\"" << ":";
  out << ")";
  return out;
}
