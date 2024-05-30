#include "command.h"

using namespace std::placeholders;

const std::string INVALID_COMMAND = "<INVALID COMMAND>";
int command::is_a_num(const std::string& str)
{
  try
  {
    return std::stoi(str);
  }
  catch (std::invalid_argument const& er)
  {
    return -1;
  }
}

void command::area(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  int num = is_a_num(arg);
  auto countFunc = [](double ac, const dyan::Polygon& polygon, int div, int mod)
    {
      double result = ac;
      if (div == -1)
      {
        if (static_cast<int>(polygon.points.size()) == mod)
        {
          result += polygon.area();
        }
      }
      else if (static_cast<int>(polygon.points.size()) % div == mod || mod == -1)
      {
        result += polygon.area();
      }
      return result;
    };
  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(countFunc, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(countFunc, _1, _2, 2, 1)) << std::endl;
    }
    else if (arg == "MEAN")
    {
      if (data.size() == 0)
      {
        throw INVALID_COMMAND;
      }
      std::cout << std::accumulate(data.begin(), data.end(), 0.0,
        std::bind(countFunc, _1, _2, 2, -1)) / data.size() << std::endl;
    }
    else
    {
      throw INVALID_COMMAND;
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0.0,
      std::bind(countFunc, _1, _2, -1, num)) << std::endl;
  }
  else
  {
    throw INVALID_COMMAND;
  }
}

void command::max(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  if (data.size() == 0)
  {
    throw INVALID_COMMAND;
  }
  if (arg == "AREA")
  {
    std::cout << std::max_element(data.begin(), data.end())->area() << std::endl;
  }
  else if (arg == "VERTEXES")
  {
    std::vector<size_t> sizeVec(data.size());
    std::transform(data.begin(), data.end(), sizeVec.begin(),
      [](const dyan::Polygon& polygon) {return polygon.points.size(); });
    std::cout << *std::max_element(sizeVec.begin(), sizeVec.end()) << std::endl;
  }
  else
  {
    throw INVALID_COMMAND;
  }
}

void command::min(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  if (data.size() == 0)
  {
    throw INVALID_COMMAND;
  }
  if (arg == "AREA")
  {
    std::cout << std::min_element(data.begin(), data.end())->area() << std::endl;
  }
  else if (arg == "VERTEXES")
  {
    std::vector<size_t> sizeVec(data.size());
    std::transform(data.begin(), data.end(), sizeVec.begin(),
      [](const dyan::Polygon& polygon) {return polygon.points.size(); });
    std::cout << *std::min_element(sizeVec.begin(), sizeVec.end()) << std::endl;
  }
  else
  {
    throw INVALID_COMMAND;
  }
}

void command::count(const std::vector<dyan::Polygon>& data)
{
  std::string arg;
  std::cin >> arg;
  int num = is_a_num(arg);
  auto countFunc = [](int ac, const dyan::Polygon& polygon, int div, int mod)
    {
      int result = ac;
      if (static_cast<int>(polygon.points.size()) % div == mod || mod == -1)
      {
        result += 1;
      }
      return result;
    };
  if (num == -1)
  {
    if (arg == "EVEN")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
        std::bind(countFunc, _1, _2, 2, 0)) << std::endl;
    }
    else if (arg == "ODD")
    {
      std::cout << std::accumulate(data.begin(), data.end(), 0,
        std::bind(countFunc, _1, _2, 2, 1)) << std::endl;
    }
    else
    {
      throw INVALID_COMMAND;
    }
  }
  else if (num > 2)
  {
    std::cout << std::accumulate(data.begin(), data.end(), 0,
      std::bind(countFunc, _1, _2, num, 0)) << std::endl;
  }
  else
  {
    throw INVALID_COMMAND;
  }
}

void command::rmecho(std::vector<dyan::Polygon>& data)
{
  dyan::Polygon target, previous;

  // Read the target polygon from input
  if (!(std::cin >> target)) {
    std::cin.clear();
    throw std::invalid_argument(INVALID_COMMAND);
  }

  int ch = 0;
  while (ch = std::cin.get() && ch != '\n' && ch != EOF) {
    if (!isspace(ch)) {
      std::cin.setstate(std::istream::failbit);
      break;
    }
  }

  if (!std::cin || data.empty()) {
    std::cin.clear();
    throw std::invalid_argument(INVALID_COMMAND);
  }

  previous = data.front();

  auto isEchoPolygon = [&target, &previous](const dyan::Polygon& current) {
    bool isEcho = (current == previous && current == target);
    previous = current;
    return isEcho;
    };

  auto newEnd = std::remove_if(data.begin() + 1, data.end(), isEchoPolygon);
  data.erase(newEnd, data.end());
}

void command::same(std::vector<dyan::Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw INVALID_COMMAND;
  }

  dyan::Polygon basic;
  std::cin >> basic;

  auto firstNonWhitespace = std::find_if_not(std::istream_iterator<char>(std::cin),
    std::istream_iterator<char>(), isspace);
  if (*firstNonWhitespace == std::iostream::traits_type::eof() or *firstNonWhitespace == int('n'))
  {
    throw INVALID_COMMAND;
  }
  if (!isspace(*firstNonWhitespace))
  {
    std::cin.setstate(std::ios_base::failbit);
    throw INVALID_COMMAND;
  }

  int count = 0;

  auto counter = [&](const dyan::Polygon polygon)
    {
      if (basic == polygon)
      {
        count++;
      }
      else
      {
        count = 0;
        return false;
      }
      return true;
    };
  count = std::count_if(polygons.begin(), polygons.end(), counter);
  std::cout << count << "\n";
}
