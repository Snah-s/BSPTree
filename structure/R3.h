#ifndef R3_H
#define R3_H

#include <cmath>

struct R3 {
  float x, y, z;

  R3 (float x = 0, float y = 0, float z = 0): x(x), y(y), z(z){}

  R3 operator+(const R3& other) const {
    return R3(x + other.x, y + other.y, z + other.z);
  }

  R3 operator-(const R3& other) const {
    return R3(x - other.x, y - other.y, z - other.z);
  }

  R3 operator*(const R3& other) const {
    return R3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
  }

  float dot(const R3& other) const {
    return x*other.x + y*other.y + z*other.z;
  }

  float magnitude() const {
    return std::sqrt(x*x + y*y + z*z);
  }

  R3 normalize() const {
    float mag = magnitude();
    if (mag == 0) return R3(0, 0, 0);
    return R3(x/mag, y/mag, z/mag);
  }
};

#endif // !R3_H
