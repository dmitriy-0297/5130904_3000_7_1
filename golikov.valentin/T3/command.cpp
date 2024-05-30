#include "command.h"

using namespace golikov;
using namespace std::placeholders;

const std::string I_C = "<INVALID COMMAND>";

//converter from string to integer
int commands::convertToNumber(const std::string& str)
{
  char* end;
  int convertedResult = strtol(str.c_str(), &end, 10);
  if (*end != 0)
  {
    return -1;
  }
  return convertedResult;
}

//get total area of figures due to parameteres(method)
void commands::getFullArea(const std::vector<golikov::Polygon>& polygons)
{
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);
  auto accumulatePolygonsArea =
    [&polygons, &number](double accumulatedArea, const golikov::Polygon& current, const std::string method)
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
      else if (method == "SPECIAL"  && current.points.size() == static_cast<size_t>(number))
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
      throw I_C;
    }
  }
  else if (number > 2)
  {
    std::cout << std::accumulate(polygons.begin(), polygons.end(), 0.0,
      std::bind(accumulatePolygonsArea, _1, _2, "SPECIAL")) << std::endl;
  }
  else
  {
    throw I_C;
  }
}

//calculate min area
void commands::getMin(const std::vector<golikov::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw I_C;

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) { return poly.points.size(); });
  auto poly = std::min_element(data.begin(), data.end());
  auto minSize = std::min_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->getArea() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *minSize << std::endl;
  else
    throw I_C;
}

//calculate max area
void commands::getMax(const std::vector<golikov::Polygon>& data)
{
  std::string arg;

  std::cin >> arg;

  if (data.size() == 0)
    throw I_C;

  std::vector<size_t> sizeVec(data.size());

  std::transform(data.begin(), data.end(), sizeVec.begin(),
    [](const Polygon& poly) { return poly.points.size(); });
  auto poly = std::max_element(data.begin(), data.end());
  auto maxSize = std::max_element(sizeVec.begin(), sizeVec.end());

  if (arg == "AREA")
    std::cout << poly->getArea() << std::endl;
  else if (arg == "VERTEXES")
    std::cout << *maxSize << std::endl;
  else
    throw I_C;
}

//calculate all figures due to parameteres(method)
void commands::countFigures(const std::vector<golikov::Polygon>& polygons)
{
  std::string argument;
  std::cin >> argument;
  int number = convertToNumber(argument);
  auto count = [&number](const golikov::Polygon& poly, const std::string& method)
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
      throw I_C;
    }
  }
  else if (number > 2)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), std::bind(count, _1, "SPECIAL")) << std::endl;
  }
  else
  {
    throw I_C;
  }
}

//get frame of figures
golikov::FrameRectangle commands::getFrameRectangle(const std::vector<golikov::Polygon>& polygons)
{
  golikov::FrameRectangle frame;
  frame.bottom_left.x = std::numeric_limits<int>::max();
  frame.bottom_left.y = std::numeric_limits<int>::max();
  frame.top_right.x = std::numeric_limits<int>::min();
  frame.top_right.y = std::numeric_limits<int>::min();
  auto comparatorwithX =
    [](const golikov::Point& pointFirst, const golikov::Point& pointSecond)
    {
      return pointFirst.x < pointSecond.x;
    };
  auto comparatorwithY =
    [](const golikov::Point& pointFirst, const golikov::Point& pointSecond)
    {
      return pointFirst.y < pointSecond.y;
    };
  frame = std::accumulate(polygons.begin(), polygons.end(), frame,
    [&](golikov::FrameRectangle frame, const golikov::Polygon& polygon)
    {
      auto min_x = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
      auto min_y = std::min_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
      auto max_x = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithX);
      auto max_y = std::max_element(polygon.points.begin(), polygon.points.end(), comparatorwithY);
      frame.bottom_left.x = std::min(frame.bottom_left.x, min_x->x);
      frame.bottom_left.y = std::min(frame.bottom_left.y, min_y->y);
      frame.top_right.x = std::max(frame.top_right.x, max_x->x);
      frame.top_right.y = std::max(frame.top_right.y, max_y->y);
      return frame;
    }
  );
  return frame;
}

void commands::checkStream()
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
    throw I_C;
  }
}

void commands::lessarea(std::vector<golikov::Polygon>& value)
{
  if (value.empty())
  {
    throw I_C;
  }

  golikov::Polygon mainEl, otherEl;
  std::cin >> mainEl;
  int prov = std::cin.get();
  for (;;)
  {
    if (prov == int('\n') || prov == std::iostream::traits_type::eof())
    {
      break;
    }
    if (!isspace(prov))
    {
      std::cin.setstate(std::ios_base::failbit);
      break;
    }
    prov = std::cin.get();
  }

  if (std::cin.fail())
  {
    std::cin.clear();
    throw I_C;
  }

  auto calcConcur = [&](const golikov::Polygon tPolygon)
    {
      otherEl = tPolygon;
      bool rez = mainEl.getArea() > otherEl.getArea();
      return rez;
    };
  std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
}

//get intersections
void commands::intersections(const std::vector<golikov::Polygon>& data)
{
  Polygon trg;

  std::cin >> trg;

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
    throw I_C;
  }

  auto cntFunc = [&trg]
  (const Polygon& poly)
    {
      return poly.isIntersect(trg);
    };

  std::cout << std::count_if(data.begin(), data.end(), cntFunc) << std::endl;
}
