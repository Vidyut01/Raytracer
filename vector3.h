#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

class Vector3 {
public:
    float e[3];

    Vector3() : e{ 0, 0, 0 } {}
    Vector3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; } /* Unmodifiable value */
    float& operator[](int i) { return e[i]; }      /* Modifiable reference */

    Vector3& operator+=(const Vector3& other) {
        e[0] += other[0];
        e[1] += other[1];
        e[2] += other[2];
        return *this;
    }

    Vector3& operator*=(const float f) {
        e[0] *= f;
        e[1] *= f;
        e[2] *= f;
        return *this;
    }

    Vector3& operator/=(const float f) { return *this *= 1/f; }

    float length() const { return std::sqrt(length_squared()); }
    float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
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
inline Vector3 operator*(const float x, const Vector3 &y) {
    return Vector3(x * y.e[0], x * y.e[1], x * y.e[2]);
}
inline Vector3 operator*(const Vector3 &x, const float y) {
    return y * x;
}

// Divide
inline Vector3 operator/(const Vector3 &x, const float y) {
    return (1/y) * x;
}

// Dot product
inline float dot(const Vector3 &x, const Vector3 &y) {
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

inline Vector3 unit_vector(const Vector3 &v) {
    return v / v.length();
}


#endif /* VECTOR3_H */
