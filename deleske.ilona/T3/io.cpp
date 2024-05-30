#include "io.h"

bool deleske::isPoint(const std::string &str)
{
  std::regex pattern("\\(-?[0-9]+;-?[0-9]+\\)");
  return std::regex_match(str, pattern);
}

std::ostream & deleske::operator<<(std::ostream &out, const deleske::Point &point)
{
  return (out << '(' << point.x << ';' << point.y << ')');
}

std::ostream & deleske::operator<<(std::ostream &out, const deleske::Polygon &polygon)
{
  out << polygon.points.size();
  for (auto &p : polygon.points)
    out << ' ' << p;
  return (out << '\n');
}

std::istream & deleske::operator>>(std::istream &in, deleske::Point &point)  // (1;1)
{
  std::istream::sentry sentry(in);

  if (!sentry)
    return in;

  std::string str;
  in >> str;
  if (!deleske::isPoint(str))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  char ch;
  std::stringstream ss(str);
  ss >> ch >> point.x >> ch >> point.y >> ch;
  return in;
}


std::istream & deleske::operator>>(std::istream &in, deleske::Polygon &polygon)  // 3 (1;2) (0;0) (0;3)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  polygon.points.clear();
  std::size_t n;
  in >> n;
  if (in.fail() || n < 3)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  polygon.points.resize(n);

  for (auto &p : polygon.points)
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> p;
  }
  if (in.peek() != '\n')
    in.setstate(std::ios_base::failbit);
  return in;
}
