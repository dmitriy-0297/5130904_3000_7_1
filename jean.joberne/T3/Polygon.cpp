#include "Polygon.h"

namespace jean {
    std::istream& operator>>(std::istream &in, Polygon &polygon) {
        int tSize;
        in >> tSize;
        if (tSize >= 3) {
            polygon.points.resize(tSize);
            for (int i = 0; i < tSize; ++i) {
                in >> polygon.points[i];
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

