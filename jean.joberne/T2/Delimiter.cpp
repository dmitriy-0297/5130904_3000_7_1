#include "Delimiter.h"

std::istream& jean::operator>>(std::istream& in, const Delimiter&& exp)
{
  std::istream::sentry guard(in);
  char current_char = 0;
  in >> current_char;
  if (current_char != exp.expected)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& jean::operator>>(std::istream& in, const StringDelimiter&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  for (size_t i = 0; exp.expected[i] != '\0'; i++) {
    in >> Delimiter{exp.expected[i]};
  }
  return in;
}

