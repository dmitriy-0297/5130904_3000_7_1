#include <functional>
#include <algorithm>
#include <numeric>

#include "functions.h"

using namespace kolpakova;
using namespace std::placeholders;

int command::isInputNumber(const std::string& str)
{
  char* end;
  int res = strtol(str.c_str(), &end, 10);

  if (*end != 0)
    return -1;
  return res;
}

void command::area(const std::vector<Polygon>& data)
{
  std::string arg;
  int num;

  std::cin >> arg;
  num = isInputNumber(arg);

  auto cntFunc = [num](double ac, const Polygon& el, int div, int rest)
    {
      double res = ac;

      if (el.points.size() % div == static_cast<size_t>(rest) || rest == -1)
        res += el.area();
      return res;
    };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(cntFunc, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(cntFunc, _1, _2, 2, 1)) << std::endl;
    }
    else if (arg == "MEAN" && data.size() != 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(cntFunc, _1, _2, 2, -1)) / data.size() << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(cntFunc, _1, _2, 0x7FFFFFFF, num)) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::min(const std::vector<kolpakova::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) {
      return poly.points.size(); 
    });
  auto poly = std::min_element(data.begin(), data.end());
  auto minSize = std::min_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *minSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::max(const std::vector<kolpakova::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) { 
      return poly.points.size(); 
    });
  auto poly = std::max_element(data.begin(), data.end());
  auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->area() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *maxSize << std::endl;
  else
    throw "<INVALID COMMAND>";
}

void command::count(const std::vector<kolpakova::Polygon>& data)
{
  std::string arg;
  int num;

  std::cin >> arg;
  num = isInputNumber(arg);

  auto cntFunc = [num]
  (const Polygon& el, int div, int rest)
    {
      return (el.points.size() % div == static_cast<size_t>(rest) || rest == -1);
    };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::count_if(data.begin(), data.end(),
        std::bind(cntFunc, _1, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::count_if(data.begin(), data.end(),
        std::bind(cntFunc, _1, 2, 1)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (num > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(cntFunc, _1, 0x7FFFFFFF, num)) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::rmecho(std::vector<kolpakova::Polygon>& data)
{
  Polygon triangle, prev;

  std::cin >> triangle;

  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (data.size() == 0)
    throw "<INVALID COMMAND>";

  prev = data[0];

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }

  auto removeCond = [&triangle, &prev]
  (const Polygon& poly)
    {
      bool res = poly == prev && poly == triangle;

      prev = poly;
      return res;
    };

  auto ri = std::remove_if(data.begin() + 1, data.end(), removeCond);
  data.erase(ri, data.end());
}

void command::intersections(const std::vector<kolpakova::Polygon>& data)
{
  Polygon triangle;

  std::cin >> triangle;

  int ch = std::cin.get();

  while (ch != int('\n') && ch != EOF)
  {
    if (!isspace(ch))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    ch = std::cin.get();
  }

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }

  auto cntFunc = [&triangle](const Polygon& poly)
    {
      return poly.isIntersect(triangle);
    };

  std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;

}

std::istream& kolpakova::operator >>(std::istream& stream, Sep&& res)
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  char ch;

  stream >> ch;
  if (!stream || ch != res.exp)
    stream.setstate(std::ios::failbit);

  return stream;
}

std::istream& kolpakova::operator >>(std::istream& stream, Point& res)
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  stream >> Sep('(') >> res.x >> Sep(';') >> res.y >> Sep(')');

  return stream;
}

std::istream& kolpakova::operator >>(std::istream& stream, Polygon& res)
{
  std::istream::sentry sentry(stream);

  if (!sentry)
    return stream;

  size_t size;

  stream >> size;

  if (size < 3)
  {
    stream.setstate(std::istream::failbit);
    return stream;
  }

  res.points.clear();
  res.points.resize(size);

  for (auto& p : res.points)
    stream >> p;

  return stream;
}

std::ostream& kolpakova::operator <<(std::ostream& stream, const Point& point)
{
  std::ostream::sentry sentry(stream);

  if (!sentry)
    return stream;

  std::cout << '(' << point.x << "; " << point.y << ")";
  return stream;
}

std::ostream& kolpakova::operator <<(std::ostream& stream, const Polygon& poly)
{
  std::ostream::sentry sentry(stream);

  if (!sentry)
    return stream;

  stream << poly.points.size() << ' ';

  for (const auto& p : poly.points)
    stream << p << ' ';

  return stream;
}