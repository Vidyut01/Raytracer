#ifndef VECTOR3_H
#define VECTOR3_H

#include "raytracer.h"
class Vector3 {
public:
    double e[3];

    Vector3() : e{ 0, 0, 0 } {}
    Vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; } /* Unmodifiable value */
    double& operator[](int i) { return e[i]; }      /* Modifiable reference */

    Vector3& operator+=(const Vector3& other) {
        e[0] += other[0];
        e[1] += other[1];
        e[2] += other[2];
        return *this;
    }

    Vector3& operator*=(const double f) {
        e[0] *= f;
        e[1] *= f;
        e[2] *= f;
        return *this;
    }

    Vector3& operator/=(const double f) { return *this *= 1/f; }

    double length() const { return std::sqrt(length_squared()); }
    double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

    static Vector3 random() {
        return Vector3(random_double(), random_double(), random_double());
    }

    static Vector3 random(double min, double max) {
        return Vector3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

    bool near_zero() const {
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }
};

using Point3 = Vector3;

/**
 *  Utility Functions
 */

// Printing
inline std::ostream& operator<<(std::ostream &out, const Vector3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Addition/Subtraction
inline Vector3 operator+(const Vector3 &x, const Vector3 &y) {
    return Vector3(x.e[0] + y.e[0], x.e[1] + y.e[1], x.e[2] + y.e[2]);
}
inline Vector3 operator-(const Vector3 &x, const Vector3 &y) {
    return Vector3(x.e[0] - y.e[0], x.e[1] - y.e[1], x.e[2] - y.e[2]);
}

// Multiply product
inline Vector3 operator*(const Vector3 &x, const Vector3 &y) {
    return Vector3(x.e[0] * y.e[0], x.e[1] * y.e[1], x.e[2] * y.e[2]);
}
inline Vector3 operator*(const double x, const Vector3 &y) {
    return Vector3(x * y.e[0], x * y.e[1], x * y.e[2]);
}
inline Vector3 operator*(const Vector3 &x, const double y) {
    return y * x;
}

// Divide
inline Vector3 operator/(const Vector3 &x, const double y) {
    return (1/y) * x;
}

// Dot product
inline double dot(const Vector3 &x, const Vector3 &y) {
    return x.e[0] * y.e[0] + x.e[1] * y.e[1] + x.e[2] * y.e[2];
}
// Cross product
inline Vector3 cross(const Vector3 &x, const Vector3 &y) {
    return Vector3(
        x.e[1] * y.e[2] - x.e[2] * y.e[1],
        x.e[2] * y.e[0] - x.e[0] * y.e[2],
        x.e[0] * y.e[1] - x.e[1] * y.e[0]
    );
}

// Unit Vector
inline Vector3 unit_vector(const Vector3 &v) {
    return v / v.length();
}
inline Vector3 random_unit_vector() {
    for (;;) {
        auto p = Vector3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1) return p / std::sqrt(lensq);
    }
}

inline Vector3 random_on_hemisphere(const Vector3 &normal) {
    Vector3 on_unit_sphere = random_unit_vector();
    return (dot(on_unit_sphere, normal) > 0) ? on_unit_sphere : -on_unit_sphere;
}

inline Vector3 reflect(const Vector3 &v, const Vector3 &normal) {
    return v - 2 * dot(v, normal) * normal;
}
inline Vector3 refract(const Vector3 &uv, const Vector3 &normal, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-uv, normal), 1.0);
    Vector3 r_out_prep = etai_over_etat * (uv + cos_theta * normal);
    Vector3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_prep.length_squared())) * normal;
    return r_out_prep + r_out_parallel;
}


#endif /* VECTOR3_H */
