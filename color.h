#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vector3.h"

using Color = Vector3;

double linear_to_gamma(double x) {
    if (x <= 0) return 0;
    return std::sqrt(x);
}

void write_color(std::ostream &out, const Color &px_color) {
    auto r = linear_to_gamma(px_color.x());
    auto g = linear_to_gamma(px_color.y());
    auto b = linear_to_gamma(px_color.z());

    static const Interval i(0.000, 0.999);
    int rb = 256 * i.clamp(r);
    int gb = 256 * i.clamp(g);
    int bb = 256 * i.clamp(b);

    out << rb << ' ' << gb << ' ' << bb << std::endl;
}

#endif /* COLOR_H */
