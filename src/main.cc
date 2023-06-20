#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"


/// Returns true if the given ray hits a sphere with given radius and center.
///
/// Explanation:
/// The equation of a sphere with radius R centered at C = <C_x, C_y, C_z> is
///
/// (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
///
/// For arbitrary Point P = (x, y, z), then
///
/// (P-C) * (P-C) = (x - C_x)^2 + (y - C_y)^2 + (z - C_z)^2 = r^2
///
/// Since P can be written as P = A + tB then
///
/// (A + tb - C) · (A + tb-C) = r^2
/// A·A + Atb - A·C + Atb + t^2 b·2 - tb·C - AC - tbC + C·2 = r^2
/// t^2 b·2 + 2t(A·b - b·C) + (A·A - 2A·C + C·C) - r^2 = 0
///
/// then solve for t that yields non-complex solutions, that is for which the
/// discriminat is greater than or equal to 0. However we don't consider t such
/// that the discriminat is equal to zero, since that does not count as a hit
///
bool hit_sphere(const Point3& center, double radius, const Ray& r) {
  // r = At - b
  // A - origin
  // b - direction
  Vec3 oc = r.origin - center;
  double a = dot(r.direction, r.direction);
  double b = 2.0 * dot(oc, r.direction);
  double c = dot(oc, oc) - radius*radius;
  double discriminant = b*b - 4*a*c;
  return discriminant > 0;
}

/// Linearly blends white and blue depending on the height of the y
/// coordinate after scaling the ray direction to unit length.
/// When t = 1.0, the color is blue and when t=0.0, the color is white.
/// For t in (0.0, 1.0), we get a linear blend.
///
/// blendedValue = (1 - t)*startValue + t*endValue;
Color ray_color(const Ray& r)  {
  if (hit_sphere(Point3(0, 0, -1), 0.5, r))
    return Color(1, 0, 0);

  Vec3 unit_direction = unit_vector(r.direction);
  auto t = 0.5*(unit_direction.y + 1.0);
  return (1.0 - t)*Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main() {

  // Image
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 2048;
  constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

  // Camera
  constexpr double viewport_height = 2.0;
  constexpr double viewport_width = aspect_ratio * viewport_height;
  constexpr double focal_length = 1.0;

  const Point3 origin = Point3(0, 0, 0);
  const Vec3 horizontal = Vec3(viewport_width, 0, 0);
  const Vec3 vertical = Vec3(0, viewport_height, 0);
  const Vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height-1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

    for (int i = 0; i < image_width; ++i) {
      double u = double(i) / (image_width - 1);
      double v = double(j) / (image_height - 1);
      Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

      Color pixel_color = ray_color(r);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
}
