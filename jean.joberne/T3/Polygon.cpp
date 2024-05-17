#include "Polygon.h"
#include <cmath>
#include <algorithm>

namespace jean {
    double Polygon::area() const {
        double accum = 0.0;
        for (size_t i = 0; i < points.size(); ++i) {
            const auto &current = points[i];
            const auto &next = points[(i + 1) % points.size()];
            accum += (current.x_ * next.y_ - next.x_ * current.y_);
        }
        return std::abs(accum * 0.5);
    }

    bool Polygon::operator==(const Polygon &other) const {
        return points == other.points;
    }

    std::istream& operator>>(std::istream &in, Polygon &polygon) {
        int size;
        if (in >> size && size >= 3) {
            polygon.points.resize(size);
            for (int i = 0; i < size; ++i) {
                if (!(in >> polygon.points[i])) {
                    in.setstate(std::ios::failbit);
                    break;
                }
            }
        } else {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream &out, const Polygon &polygon) {
        out << polygon.points.size();
        for (const auto &point : polygon.points) {
            out << ' ' << point;
        }
        return out;
    }
}

