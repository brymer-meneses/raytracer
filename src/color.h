#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

class Color : public Vec3 {
  public:
    double& r = x;
    double& g = y;
    double& b = z;

  Color(double r, double g, double b) : Vec3(r, g, b) {}

  Color(const Vec3& vec) : Vec3(vec.x, vec.y, vec.z) {}
};

inline void write_color(std::ostream& out, Color pixel_color) {
  out << static_cast<int>(255.999 * pixel_color.r) << ' '
      << static_cast<int>(255.999 * pixel_color.g) << ' '
      << static_cast<int>(255.999 * pixel_color.b) << ' ';
}

#endif
