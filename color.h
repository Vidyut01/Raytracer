#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vector3.h"

using Color = Vector3;

void write_color(std::ostream &out, const Color &px_color) {
    auto r = px_color.x();
    auto g = px_color.y();
    auto b = px_color.z();

    static const Interval i(0.000, 0.999);
    int rb = 256 * i.clamp(r);
    int gb = 256 * i.clamp(g);
    int bb = 256 * i.clamp(b);

    out << rb << ' ' << gb << ' ' << bb << std::endl;
}

#endif /* COLOR_H */
