#ifndef COLOR_H
#define COLOR_H

#include "vector3.h"

#include <iostream>

using color = Vector3;

void write_color(std::ostream &out, const color &px_color) {
    auto r = px_color.x();
    auto g = px_color.y();
    auto b = px_color.z();

    int rb = 255.999 * r;
    int gb = 255.999 * g;
    int bb = 255.999 * b;

    out << rb << ' ' << gb << ' ' << bb << std::endl;
}

#endif /* COLOR_H */
