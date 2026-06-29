#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max-min) * random_double();
}


#include "color.h"
#include "ray.h"
#include "vector3.h"
#include "interval.h"

#define Color_White Color(1.0, 1.0, 1.0)
#define Color_Sky Color(0.5, 0.7, 1.0)
#define Color_Red Color(1.0, 0.0, 0.0)

#endif /* RAYTRACER_H */
