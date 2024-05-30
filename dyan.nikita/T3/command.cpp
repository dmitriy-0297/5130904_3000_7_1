#include "command.h"

using namespace std::placeholders;

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
int command::is_a_num(const std::string& str)
{
  try
  {
    return std::stoi(str);
  }
  catch (const std::invalid_argument&)
  {
    return -1;
  }
}

void command::area(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  int num = is_a_num(arg);

  auto areaAccumulator = [](double acc, const dyan::Polygon& plg, int div, int mod)
    {
      if (div == -1 && static_cast<int>(plg.points.size()) == mod)
      {
        acc += plg.area();
      }
      else if (static_cast<int>(plg.points.size()) % div == mod || mod == -1)
      {
        acc += plg.area();
      }
      return acc;
    };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(areaAccumulator, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(areaAccumulator, _1, _2, 2, 1)) << std::endl;
    }
    else if (arg == "MEAN")
    {
      if (data.empty())
      {
        throw std::invalid_argument(INVALID_COMMAND);
      }
      double totalArea = std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(areaAccumulator, _1, _2, 2, -1));
      std::cout << totalArea / data.size() << std::endl;
    }
    else
    {
      throw std::invalid_argument(INVALID_COMMAND);
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(areaAccumulator, _1, _2, -1, num)) << std::endl;
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::max(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;

  if (data.empty())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }

  if (arg == "AREA")
  {
    auto maxArea = std::max_element(data.begin(), data.end(),
      [](const dyan::Polygon& a, const dyan::Polygon& b) { return a.area() < b.area(); });
    std::cout << maxArea->area() << std::endl;
  }
  else if (arg == "VERTEXES")
  {
    auto maxVertexes = std::max_element(data.begin(), data.end(),
      [](const dyan::Polygon& a, const dyan::Polygon& b)
      { return a.points.size() < b.points.size(); });
    std::cout << maxVertexes->points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::min(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;

  if (data.empty())
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }

  if (arg == "AREA")
  {
    auto minArea = std::min_element(data.begin(), data.end(),
      [](const dyan::Polygon& a, const dyan::Polygon& b) { return a.area() < b.area(); });
    std::cout << minArea->area() << std::endl;
  }
  else if (arg == "VERTEXES")
  {
    auto minVertexes = std::min_element(data.begin(), data.end(),
      [](const dyan::Polygon& a, const dyan::Polygon& b)
      {
        return a.points.size() < b.points.size();
      });
    std::cout << minVertexes->points.size() << std::endl;
  }
  else
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }
}

void command::count(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  int num = is_a_num(arg);

  auto countAccumulator = [](int acc, const dyan::Polygon& plg, int div, int mod)
    {
      if (static_cast<int>(plg.points.size()) % div == mod || mod == -1)
      {
        acc++;
      }
      return acc;
    };

  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
        std::bind(countAccumulator, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
        std::bind(countAccumulator, _1, _2, 2, 1)) << std::endl;
    }
    else
    {
      throw std::invalid_argument(INVALID_COMMAND);
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0,
      std::bind(countAccumulator, _1, _2, num, 0)) << std::endl;
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

  if (data.empty())
  {
    std::cout << 0 << std::endl;
    return;
  }

  prev = data[0];
  int count = 0;

  auto removeCond = [&target, &prev, &count](const dyan::Polygon& plg)
    {
      bool result = (plg == prev && plg == target);
      prev = plg;
      if (result)
      {
        count++;
      }
      return result;
    };

  auto newEnd = std::remove_if(data.begin() + 1, data.end(), removeCond);
  data.erase(newEnd, data.end());
  std::cout << count << std::endl;
}

void command::same(std::vector<dyan::Polygon>& data)
{
  dyan::Polygon target;
  std::cin >> target;

  if (!std::cin)
  {
    throw std::invalid_argument(INVALID_COMMAND);
  }

  std::sort(target.points.begin(), target.points.end());

  auto countFunc = [&target](const dyan::Polygon& plg)
    {
      return plg.is_overlay_compatible(target);
    };

  std::cout << std::count_if(data.begin(), data.end(), countFunc) << std::endl;
}
