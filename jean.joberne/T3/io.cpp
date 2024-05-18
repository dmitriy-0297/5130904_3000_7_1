#include "Command.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>

namespace cmd {
    const std::string I_C = "<INVALID COMMAND>";

    int validStringToInt(const std::string &str) {
        char *end;
        int num = std::strtol(str.c_str(), &end, 10);
        return (*end == '\0' && end != str.c_str()) ? num : -1;
    }

    void area(const std::vector<jean::Polygon> &polygons, const std::string &param) {
        double result = 0.0;
        int divisor = 2, remains = -1;
        if (param == "EVEN") remains = 0;
        else if (param == "ODD") remains = 1;
        else if (param == "MEAN") divisor = remains = -1;
        else if ((divisor = validStringToInt(param)) <= 2) {
            throw I_C;
        }

        if (remains == -1) {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [=](double acc, const jean::Polygon &p) { return acc + p.area(); });
            if (param == "MEAN") result /= polygons.size();
        } else {
            result = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [=](double acc, const jean::Polygon &p) {
                    return acc + ((static_cast<int>(p.points.size()) % divisor == remains) ? p.area() : 0);
                });
        }

        std::cout << std::fixed << std::setprecision(1) << result << "\n";
    }

    void max(const std::vector<jean::Polygon> &polygons, const std::string &param) {
        if (polygons.empty()) throw I_C;
        if (param == "AREA") {
            auto maxArea = std::max_element(polygons.begin(), polygons.end(),
                [](const jean::Polygon &a, const jean::Polygon &b) { return a.area() < b.area(); });
            std::cout << std::fixed << std::setprecision(1) << maxArea->area() << "\n";
        } else if (param == "VERTEXES") {
            auto maxVertices = std::max_element(polygons.begin(), polygons.end(),
                [](const jean::Polygon &a, const jean::Polygon &b) { return a.points.size() < b.points.size(); });
            std::cout << maxVertices->points.size() << "\n";
        } else {
            throw I_C;
        }
    }

    void min(const std::vector<jean::Polygon> &polygons, const std::string &param) {
        if (polygons.empty()) throw I_C;
        if (param == "AREA") {
            auto minArea = std::min_element(polygons.begin(), polygons.end(),
                [](const jean::Polygon &a, const jean::Polygon &b) { return a.area() < b.area(); });
            std::cout << std::fixed << std::setprecision(1) << minArea->area() << "\n";
        } else if (param == "VERTEXES") {
            auto minVertices = std::min_element(polygons.begin(), polygons.end(),
                [](const jean::Polygon &a, const jean::Polygon &b) { return a.points.size() < b.points.size(); });
            std::cout << minVertices->points.size() << "\n";
        } else {
            throw I_C;
        }
    }

    void count(const std::vector<jean::Polygon> &polygons, const std::string &param) {
        int divisor = 2, remains = -1;
        if (param == "EVEN") remains = 0;
        else if (param == "ODD") remains = 1;
        else if ((divisor = validStringToInt(param)) <= 2) {
            throw I_C;
        }

        auto count = std::count_if(polygons.begin(), polygons.end(),
            [=](const jean::Polygon &p) { return static_cast<int>(p.points.size()) % divisor == remains; });
        std::cout << count << "\n";
    }

    void lessArea(const std::vector<jean::Polygon> &polygons) {
        if (polygons.empty()) throw I_C;
        jean::Polygon refPolygon;
        if (!(std::cin >> refPolygon)) throw I_C;

        auto count = std::count_if(polygons.begin(), polygons.end(),
            [&](const jean::Polygon &p) { return p.area() < refPolygon.area(); });
        std::cout << count << "\n";
    }

    void maxSeq(const std::vector<jean::Polygon> &polygons) {
        if (polygons.empty()) throw I_C;
        jean::Polygon refPolygon;
        if (!(std::cin >> refPolygon)) throw I_C;

        int maxCount = 0, currentCount = 0;
        for (const auto &p : polygons) {
            if (p == refPolygon) {
                currentCount++;
                maxCount = std::max(maxCount, currentCount);
            } else {
                currentCount = 0;
            }
        }
        std::cout << maxCount << "\n";
    }
}

