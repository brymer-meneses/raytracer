#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

/// Linearly blends white and blue depending on the height of the y
/// coordinate after scaling the ray direction to unit length.
/// When t = 1.0, the color is blue and when t=0.0, the color is white.
/// For t in (0.0, 1.0), we get a linear blend.
///
/// blendedValue = (1 - t)*startValue + t*endValue;
Color ray_color(const Ray& r)  {
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
