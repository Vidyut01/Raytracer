#include "color.h"
#include "vector3.h"
#include "ray.h"

#include <iostream>

double hit_sphere(const Point3 &center, double radius, const Ray &r) {
    Vector3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = h*h - a*c;

    if (discriminant < 0) return -1.0;
    return (h - std::sqrt(discriminant)) / a;
}

// tmp define, the numbers were confusing
#define Color_White Color(1.0, 1.0, 1.0)
#define Color_Sky Color(0.5, 0.7, 1.0)
#define Color_Red Color(1.0, 0.0, 0.0)

#define Circle_Center Point3(0,0,-1)
#define Circle_Radius 0.5

Color ray_color(const Ray &r) {
    auto t = hit_sphere(Circle_Center, Circle_Radius, r);
    if (t > 0) {
        Vector3 N = unit_vector(r.at(t) - Circle_Center);
        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    Vector3 unit_dir = unit_vector(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * Color_White + a * Color_Sky;
}

int main(int argc, char const *argv[])
{
    auto aspect_ratio = 16.0 / 9.0;
    int width = 400;
    int height = (height = width / aspect_ratio) >= 1 ? height : 1;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * ((double)(width) / height);
    auto camera_center = Point3(0, 0, 0);

    auto viewport_x = Vector3(viewport_width, 0, 0);
    auto viewport_y = Vector3(0, -viewport_height, 0);

    auto px_delta_x = viewport_x / width;
    auto px_delta_y = viewport_y / height;

    auto viewport_upper_left = camera_center - Vector3(0, 0, focal_length) - viewport_x / 2 - viewport_y / 2;
    auto px00_loc = viewport_upper_left + 0.5 * (px_delta_x + px_delta_y);


    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int j = 0; j < height; ++j) {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            auto px_center = px00_loc + i * px_delta_x + j * px_delta_y;
            auto ray_dir = px_center - camera_center;
            Ray r(camera_center, ray_dir);

            auto px_color = ray_color(r);
            write_color(std::cout, px_color);
        }
    }
    std::clog << "\rDone.                 \n";

    return 0;
}
