#ifndef RAY_H
#define RAY_H

#include "point3.h"

class Ray {
  public:
    Point3 origin;
    Vec3 direction;

  public:
    Ray() {}
    Ray(const Point3& origin, const Vec3& direction) 
      : origin(origin), direction(direction) {}
    
    auto at(double t) const -> Point3 {
      return origin + t * direction;
    }
    
};

#endif
