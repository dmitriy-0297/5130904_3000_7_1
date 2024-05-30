#ifndef DELIMETER_H
#define DELIMETER_H
#include <iostream>
struct Delimiter
{
  char delimiter;
};

std::istream& operator>>(std::istream& in, const Delimiter&& exp);

struct DelimiterString
{
  const char* delimiter;
};

std::istream& operator>>(std::istream& in, DelimiterString&& exp);
#endif
