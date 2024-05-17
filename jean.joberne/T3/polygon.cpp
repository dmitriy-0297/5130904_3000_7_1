#include "Polygon.h"
#include <cmath>
#include <numeric>
#include <iomanip>

namespace jean {
    double Polygon::area() const {
        double accum = 0.0;
        for (size_t i = 0; i < points.size(); i++) {
            const auto &current = points[i];
            const auto &next = points[(i + 1) % points.size()];
            accum += (current.x_ * next.y_ - next.x_ * current.y_);
        }
        return std::abs(accum * 0.5);
    }

    bool Polygon::operator==(const Polygon &other) const {
        return points.size() == other.points.size() && std::equal(points.begin(), points.end(), other.points.begin());
    }

    std::istream& operator>>(std::istream &in, Polygon &polygon) {
        int numPoints;
        if (in >> numPoints && numPoints >= 3) {
            polygon.points.resize(numPoints);
            for (auto &point : polygon.points) {
                in >> point;
            }
        } else {
            in.setstate(std::ios_base::failbit);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream &out, const Polygon &polygon) {
        out << polygon.points.size() << " ";
        for (const auto &point : polygon.points) {
            out << point << " ";
        }
        return out;
    }
}

