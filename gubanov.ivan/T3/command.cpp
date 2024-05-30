#include "command.h"

int command::convertToNumber(const std::string& str)
{
  char* end;
  int convertedResult = strtol(str.c_str(), &end, 10);
  if (*end != 0)
  {
    return -1;
  }
  return convertedResult;
}

void command::getTotalArea(const std::vector<gubanov::Polygon>& polygons)
{
  using namespace std::placeholders;
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);
  auto accumulatePolygonsArea =
    [&polygons, &number](double accumulatedArea, const gubanov::Polygon& current, const std::string method)
    {
      double result = accumulatedArea;
      if (method == "EVEN" && current.points.size() % 2 == 0)
      {
        result += current.getArea();
      }
      else if (method == "ODD" && current.points.size() % 2 != 0)
      {
        result += current.getArea();
      }
      else if (method == "MEAN")
      {
        result += current.getArea();
      }
      else if (method == "SPECIAL" && current.points.size() == static_cast<size_t>(number))
      {
        result += current.getArea();
      }
      return result;
    };
  if (number == -1)
  {
    if (argument == "EVEN" || argument == "ODD")
    {
      std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(accumulatePolygonsArea, _1, _2, argument)) << std::endl;
    }
    else if (argument == "MEAN" && polygons.size() != 0)
    {
      std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(accumulatePolygonsArea, _1, _2, argument)) / polygons.size() << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (number > 2)
  {
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      std::bind(accumulatePolygonsArea, _1, _2, "SPECIAL")) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::calculateMinOrMax(const std::vector<gubanov::Polygon>& polygons, const std::string& method)
{
  std::string argument;
  std::cin >> argument;
  if (polygons.size() == 0)
  {
    throw "<INVALID COMMAND>";
  }

  std::vector<size_t> sizeVector(polygons.size());

  std::transform(polygons.begin(), polygons.end(), sizeVector.begin(),
    [](const gubanov::Polygon& current)
    {
      return current.points.size();
    }
  );
  if (argument == "AREA")
  {
    if (method == "MIN")
    {
      std::cout << std::min_element(polygons.begin(), polygons.end())->getArea() << std::endl;
    }
    else
    {
      std::cout << std::max_element(polygons.begin(), polygons.end())->getArea() << std::endl;
    }
  }
  else if (argument == "VERTEXES")
  {
    if (method == "MAX")
    {
      std::cout << *std::max_element(sizeVector.begin(), sizeVector.end()) << std::endl;
    }
    else
    {
      std::cout << *std::min_element(sizeVector.begin(), sizeVector.end()) << std::endl;
    }
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

void command::countPolygons(const std::vector<gubanov::Polygon>& polygons)
{
  using namespace std::placeholders;
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);
  auto count = [&number](const gubanov::Polygon& poly, const std::string& method)
    {
      if (method == "EVEN")
      {
        return poly.points.size() % 2 == 0;
      }
      else if (method == "ODD")
      {
        return poly.points.size() % 2 != 0;
      }
      else if (method == "SPECIAL")
      {
        return poly.points.size() == static_cast<size_t>(number);
      }
      return false;
    };
  if (number == -1)
  {
    if (argument == "EVEN" || argument == "ODD")
    {
      std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, argument)) << std::endl;
    }
    else
    {
      throw "<INVALID COMMAND>";
    }
  }
  else if (number > 2)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, "SPECIAL")) << std::endl;
  }
  else
  {
    throw "<INVALID COMMAND>";
  }
}

gubanov::FrameRectangle command::getFrameRectangle(const std::vector<gubanov::Polygon>& polygons)
{
  gubanov::FrameRectangle rect;
  rect.bottom_left.x = std::numeric_limits<int>::max();
  rect.bottom_left.y = std::numeric_limits<int>::max();
  rect.top_right.x = std::numeric_limits<int>::min();
  rect.top_right.y = std::numeric_limits<int>::min();
  auto comparatorwithX =
    [](const gubanov::Point& pointFirst, const gubanov::Point& pointSecond)
    {
      return pointFirst.x < pointSecond.x;
    };
  auto comparatorwithY =
    [](const gubanov::Point& pointFirst, const gubanov::Point& pointSecond)
    {
      return pointFirst.y < pointSecond.y;
    };
  rect = std::accumulate(polygons.begin(), polygons.end(), rect,
    [&](gubanov::FrameRectangle rect, const gubanov::Polygon& polygon)
    {
      auto min_x = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
      auto min_y = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
      auto max_x = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
      auto max_y = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
      rect.bottom_left.x = std::min(rect.bottom_left.x, min_x->x);
      rect.bottom_left.y = std::min(rect.bottom_left.y, min_y->y);
      rect.top_right.x = std::max(rect.top_right.x, max_x->x);
      rect.top_right.y = std::max(rect.top_right.y, max_y->y);
      return rect;
    }
  );
  return rect;
}

void command::checkStream()
{
  int streamState = std::cin.get();

  while (streamState != int('\n') && streamState != EOF)
  {
    if (!isspace(streamState))
    {
      std::cin.setstate(std::istream::failbit);
      break;
    }
    streamState = std::cin.get();
  }

  if (!std::cin)
  {
    std::cin.clear();
    throw "<INVALID COMMAND>";
  }
}

void command::InFrame(const std::vector<gubanov::Polygon>& polygons)
{
  gubanov::Polygon polygon_param;
  std::cin >> polygon_param;
  checkStream();
  gubanov::FrameRectangle frame = getFrameRectangle(polygons);
  if (std::all_of(polygon_param.points.begin(), polygon_param.points.end(),
    [&frame](const gubanov::Point& point)
    {
      return point.x >= frame.bottom_left.x && point.x <= frame.top_right.x &&
        point.y >= frame.bottom_left.y && point.y <= frame.top_right.y;
    }))
  {
    std::cout << "<TRUE>\n";
  }
  else
  {
    std::cout << "<FALSE>\n";
  }
}

void command::echo(std::vector<gubanov::Polygon>& polygons)
{
  gubanov::Polygon polygon_param;
  std::cin >> polygon_param;
  checkStream();
  std::vector<gubanov::Polygon> result = std::accumulate(polygons.begin(), polygons.end(), std::vector<gubanov::Polygon>(),
    [&polygon_param](std::vector<gubanov::Polygon> acc, const gubanov::Polygon& poly)
    {
      if (poly == polygon_param)
      {
        acc.push_back(poly);
        acc.push_back(polygon_param);
      }
      else
      {
        acc.push_back(poly);
      }
      return acc;
    });
  std::cout << std::count(polygons.begin(), polygons.end(), polygon_param) << '\n';
  polygons = result;
}
