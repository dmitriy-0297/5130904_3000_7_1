        #include <iostream>
        #include <fstream>
        #include <algorithm>
        #include <functional>
        #include <exception>
        #include <string>
        #include <sstream>
        #include <iterator>
        #include <iomanip>
        #include "Header1.h"
        #include "Header2.h"

        const std::string I_C = "<INVALID COMMAND>";
        const std::string I_CMD = "<INVALID COMMAND>";

        int cmd::validStringToInt(std::string str)
        {
            char* end;
            int sInt = strtol(str.c_str(), &end, 10);
            if (*end != '\0' || end == str.c_str())
            {
                return -1;
            }
            return static_cast<int>(sInt);
        }

        void cmd::area(std::vector<geometry::Polygon>& value, const std::string str)
        {
            int data = 0;
            int maxDivisor = std::numeric_limits<int>::max();
            size_t vSize = value.size();
            data = validStringToInt(str);
            auto calcArea = [](int divisor, int remains, double initial, const geometry::Polygon& elem)
                {
                    double rez = initial;
                    return rez + (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1 ? elem.area() : 0);
                };

            if (data == -1)
            {
                if (str == "EVEN")
                {
                    std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                        std::bind(calcArea, 2, 0, std::placeholders::_1, std::placeholders::_2)) << "\n";
                }
                else if (str == "ODD")
                {
                    std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                        std::bind(calcArea, 2, 1, std::placeholders::_1, std::placeholders::_2)) << "\n";
                }
                else if (str == "MEAN" && value.size() != 0)
                {
                    std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                        std::bind(calcArea, 2, -1, std::placeholders::_1, std::placeholders::_2)) / vSize << "\n";
                }
                else
                {
                    throw I_C;
                }
            }
            else if (data > 2)
            {
                std::cout << std::fixed << std::setprecision(1) << std::accumulate(value.begin(), value.end(), 0.0,
                    std::bind(calcArea, maxDivisor, data, std::placeholders::_1, std::placeholders::_2)) << "\n";
            }
            else
            {
                throw I_C;
            }
        }

        void cmd::max(std::vector<geometry::Polygon>& value, const std::string str)
        {
            if (value.empty())
            {
                throw I_C;
            }
            if (str == "AREA")
            {
                auto maxArea = *std::max_element(value.begin(), value.end(),
                    [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                    {
                        return p1.area() < p2.area();
                    });
                std::cout << std::fixed << std::setprecision(1) << maxArea.area() << "\n";
            }
            else if (str == "VERTEXES")
            {
                auto maxVertexes = *std::max_element(value.begin(), value.end(),
                    [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                    {
                        return p1.points.size() < p2.points.size();
                    });
                std::cout << maxVertexes.points.size() << "\n";
            }
            else
            {
                throw I_C;
            }
        }

        void cmd::min(std::vector<geometry::Polygon>& value, const std::string str)
        {
            if (value.empty())
            {
                throw I_C;
            }
            if (str == "AREA")
            {
                auto minArea = *std::min_element(value.begin(), value.end(),
                    [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                    {
                        return p1.area() < p2.area();
                    });
                std::cout << std::fixed << std::setprecision(1) << minArea.area() << "\n";
            }
            else if (str == "VERTEXES")
            {
                auto minVertexes = *std::min_element(value.begin(), value.end(),
                    [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                    {
                        return p1.points.size() < p2.points.size();
                    });
                std::cout << minVertexes.points.size() << "\n";
            }
            else
            {
                throw I_C;
            }
        }

        void cmd::count(std::vector<geometry::Polygon>& value, const std::string str)
        {
            int data = 0;
            int maxDivisor = std::numeric_limits<int>::max();
            data = validStringToInt(str);
            auto calcConcur = [](int divisor, int remains, const geometry::Polygon& elem)
                {
                    return (elem.points.size() % divisor == static_cast<size_t>(remains) || remains == -1);
                };

            if (data == -1)
            {
                if (str == "EVEN")
                {
                    std::cout << std::count_if(value.begin(), value.end(),
                        std::bind(calcConcur, 2, 0, std::placeholders::_1)) << "\n";
                }
                else if (str == "ODD")
                {
                    std::cout << std::count_if(value.begin(), value.end(),
                        std::bind(calcConcur, 2, 1, std::placeholders::_1)) << "\n";
                }
            }
            else if (data > 2)
            {
                std::cout << std::count_if(value.begin(), value.end(),
                    std::bind(calcConcur, maxDivisor, data, std::placeholders::_1)) << "\n";
            }
            else
            {
                throw I_C;
            }
        }

        void cmd::lessArea(std::vector<geometry::Polygon>& value)
        {
            if (value.empty())
            {
                throw I_C;
            }

            geometry::Polygon mainEl, otherEl;
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

            auto calcConcur = [&](const geometry::Polygon tPolygon)
                {
                    otherEl = tPolygon;
                    bool rez = mainEl.area() > otherEl.area();
                    return rez;
                };
            std::cout << std::count_if(value.begin(), value.end(), calcConcur) << "\n";
        }

        void cmd::maxSeq(std::vector<geometry::Polygon>& value)
        {
            if (value.empty())
            {
                throw I_C;
            }

            geometry::Polygon mainEl;
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

            int maxCount = 0;
            int currentCount = 0;

            auto counter = [&](const geometry::Polygon tPolygon)
                {
                    if (mainEl == tPolygon)
                    {
                        currentCount++;
                    }
                    else
                    {
                        maxCount = std::max(maxCount, currentCount);
                        currentCount = 0;
                        return false;
                    }
                    return true;
                };
            currentCount = std::count_if(value.begin(), value.end(), counter);
            maxCount = std::max(maxCount, currentCount);
            std::cout << maxCount << "\n";
        }

        void cmd::echo(std::vector<geometry::Polygon>& value)
        {
            if (value.empty())
            {
                throw I_C;
            }

            geometry::Polygon mainEl;
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

            int count = 0;
            for (auto it = value.begin(); it != value.end(); ++it)
            {
                if (*it == mainEl)
                {
                    it = value.insert(it + 1, mainEl);
                    ++count;
                }
            }
            std::cout << count << "\n";
        }

        void cmd::inFrame(std::vector<geometry::Polygon>& value)
        {
            if (value.empty())
            {
                throw I_C;
            }

            geometry::Polygon mainEl;
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

            auto minMaxX = std::minmax_element(value.begin(), value.end(),
                [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                {
                    return std::min_element(p1.points.begin(), p1.points.end(), [](const geometry::Point& p1, const geometry::Point& p2)
                        {
                            return p1.x_ < p2.x_;
                        })->x_ < std::min_element(p2.points.begin(), p2.points.end(), [](const geometry::Point& p1, const geometry::Point& p2)
                            {
                                return p1.x_ < p2.x_;
                            })->x_;
                });

            auto minMaxY = std::minmax_element(value.begin(), value.end(),
                [](const geometry::Polygon& p1, const geometry::Polygon& p2)
                {
                    return std::min_element(p1.points.begin(), p1.points.end(), [](const geometry::Point& p1, const geometry::Point& p2)
                        {
                            return p1.y_ < p2.y_;
                        })->y_ < std::min_element(p2.points.begin(), p2.points.end(), [](const geometry::Point& p1, const geometry::Point& p2)
                            {
                                return p1.y_ < p2.y_;
                            })->y_;
                });

            auto xMin = std::min_element(minMaxX.first->points.begin(), minMaxX.first->points.end(),
                [](const geometry::Point& p1, const geometry::Point& p2)
                {
                    return p1.x_ < p2.x_;
                })->x_;

            auto xMax = std::max_element(minMaxX.second->points.begin(), minMaxX.second->points.end(),
                [](const geometry::Point& p1, const geometry::Point& p2)
                {
                    return p1.x_ < p2.x_;
                })->x_;

            auto yMin = std::min_element(minMaxY.first->points.begin(), minMaxY.first->points.end(),
                [](const geometry::Point& p1, const geometry::Point& p2)
                {
                    return p1.y_ < p2.y_;
                })->y_;

            auto yMax = std::max_element(minMaxY.second->points.begin(), minMaxY.second->points.end(),
                [](const geometry::Point& p1, const geometry::Point& p2)
                {
                    return p1.y_ < p2.y_;
                })->y_;

            bool inFrame = std::all_of(mainEl.points.begin(), mainEl.points.end(),
                [xMin, xMax, yMin, yMax](const geometry::Point& p)
                {
                    return p.x_ >= xMin && p.x_ <= xMax && p.y_ >= yMin && p.y_ <= yMax;
                });

            std::cout << (inFrame ? "<TRUE>" : "<FALSE>") << "\n";
        }

        int main(int argc, char* argv[])
        {
            if (argc != 2)
            {
                std::cerr << "Misapplication" << "\n";
                std::cout << "Usage: program_name <filename>" << "\n";
                return EXIT_FAILURE;
            }
            std::string fileName = argv[1];
            std::ifstream file(fileName);
            if (!file)
            {
                std::cerr << "Error: file didn't open" << "\n";
                return EXIT_FAILURE;
            }
            std::vector<geometry::Polygon> value;
            while (!file.eof())
            {
                std::transform(std::istream_iterator<geometry::Polygon>(file),
                    std::istream_iterator<geometry::Polygon>(),
                    std::back_inserter(value), [](const geometry::Polygon& poly)
                    {
                        return poly;
                    });
                if (!file.eof() && file.fail())
                {
                    file.clear();
                    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            try
            {
                for (;;)
                {
                    std::string str;
                    if (!(std::getline(std::cin, str, '\n') && !str.empty() && !(std::cin.eof())))
                    {
                        break;
                    }
                    std::string comnd1, comnd2;
                    std::istringstream iss(str);
                    iss >> comnd1 >> comnd2;

                    try
                    {
                        if (comnd1 == "AREA")
                        {
                            cmd::area(value, comnd2);
                        }
                        else if (comnd1 == "MAX")
                        {
                            cmd::max(value, comnd2);
                        }
                        else if (comnd1 == "MIN")
                        {
                            cmd::min(value, comnd2);
                        }
                        else if (comnd1 == "COUNT")
                        {
                            cmd::count(value, comnd2);
                        }
                        else if (comnd1 == "MAXSEQ")
                        {
                            cmd::maxSeq(value);
                        }
                        else if (comnd1 == "LESSAREA")
                        {
                            cmd::lessArea(value);
                        }
                        else if (comnd1 == "ECHO")
                        {
                            cmd::echo(value);
                        }
                        else if (comnd1 == "INFRAME")
                        {
                            cmd::inFrame(value);
                        }
                        else if (comnd1 != "")
                        {
                            throw I_CMD;
                        }
                    }
                    catch (const std::string k)
                    {
                        std::cout << k << "\n";
                    }
                }
                return EXIT_SUCCESS;
            }
            catch (...)
            {
                std::cerr << "Wrong: Something went wrong" << "\n";
                return EXIT_FAILURE;
            }
        }
