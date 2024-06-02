#include "command.h"

using namespace std::placeholders;

const std::string INVALID_COMMAND = "<INVALID COMMAND>";

int command::is_a_num(const std::string& str)
{
  char* end;
  int num = strtol(str.c_str(), &end, 10);
  if (*end != 0)
  {
    return -1;
  }
  return num;
}


void command::area(const std::vector<dyan::Polygon>& data, const std::string& arg)
{
  auto accumulateArea = [](double ac, const dyan::Polygon& polygon, std::size_t mod2, std::size_t vertices)
    {
      if ((polygon.points.size() % 2 == mod2) || (mod2 == 2 && polygon.points.size() == vertices) || (mod2 == 3))
      {
        ac += polygon.area();
      }
      return ac;
    };

  int num = is_a_num(arg);

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(accumulateArea, _1, _2, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(accumulateArea, _1, _2, 1, 0)) << '\n';
    }
    else if (arg == "MEAN" && data.size() != 0)
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(accumulateArea, _1, _2, 3, 0)) / data.size() << std::endl;
    }
    else
    {
      throw std::invalid_argument(INVALID_COMMAND);
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(accumulateArea, _1, _2, 2, num)) << '\n';
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::max(const std::vector<dyan::Polygon>& data, const std::string& arg)
{
  if (data.empty())
    throw std::invalid_argument(INVALID_COMMAND);

  if (arg == "AREA")
  {
    std::cout << std::max_element(data.begin(), data.end())->area() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t max, const dyan::Polygon& poly)
      {
        return (poly.points.size() > max ? poly.points.size() : max);
      }
    ) << '\n';
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::min(const std::vector<dyan::Polygon>& data, const std::string& arg)
{
  if (data.empty())
    throw std::invalid_argument(INVALID_COMMAND);

  if (arg == "AREA")
  {
    std::cout << std::min_element(data.begin(), data.end())->area() << '\n';
  }
  else if (arg == "VERTEXES")
  {
    std::vector<std::size_t> sizes(data.size());

    std::cout << std::accumulate(
      data.begin() + 1,
      data.end(),
      data[0].points.size(),
      [](std::size_t min, const dyan::Polygon& polygon)
      {
        return (polygon.points.size() < min ? polygon.points.size() : min);
      }
    ) << '\n';
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::count(const std::vector<dyan::Polygon>& data, const std::string& arg)
{
  auto countPolygons = [](const dyan::Polygon& polygon, std::size_t mod2, std::size_t vertices)
    {
      return ((polygon.points.size() % 2 == mod2) || (mod2 == 2 && polygon.points.size() == vertices));
    };

  int num = is_a_num(arg);

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::count_if(data.begin(), data.end(),
        std::bind(countPolygons, _1, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
      std::cout << std::count_if(data.begin(), data.end(),
        std::bind(countPolygons, _1, 1, 0)) << '\n';
    }
    else
    {
      throw std::invalid_argument(INVALID_COMMAND);
    }
  }
  else if (num > 2)
  {
    std::cout << std::count_if(data.begin(), data.end(),
      std::bind(countPolygons, _1, 2, stoi(arg))) << '\n';
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::rmecho(std::vector<dyan::Polygon>& data)
{
  dyan::Polygon target, prev;
  std::cin >> target;
  prev = data[0];
  int count = 0;
  auto removeCond = [&target, &prev, &count](const dyan::Polygon& polygon) {
    bool result = polygon == prev && polygon == target;
    prev = polygon;
    if (result)
    {
      count++;
    }
    return result;
    };
  auto removeFunc = std::remove_if(data.begin() + 1, data.end(), removeCond);
  data.erase(removeFunc, data.end());
  std::cout << count << std::endl;
}

void command::same(const std::vector<dyan::Polygon>& data, dyan::Polygon& target)
{
  if (std::cin.fail() || std::cin.get() != '\n')
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
  else
  {
    std::sort(target.points.begin(), target.points.end());
    auto countFunc = [&target](const dyan::Polygon& polygon)
      {
        return polygon.isOverlayCompatible(target);
      };
    std::cout << std::count_if(data.begin(), data.end(), countFunc) << std::endl;
  }
}
