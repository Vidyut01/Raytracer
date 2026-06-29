#ifndef CAMERA_H
#define CAMERA_H

#include "object_list.h"

class Camera {
private:
    double aspect_ratio = 16.0 / 9.0;
    int width = 400;
    int samples_per_px = 100;

    double px_samples_scale;
    int height;
    Point3 px00_loc, px_delta_x, px_delta_y, camera_center;

public:
    Camera() {
        height = (height = width / aspect_ratio) >= 1 ? height : 1;
        auto focal_length = 1.0;

        px_samples_scale = 1.0 / samples_per_px;

        camera_center = Point3(0, 0, 0);
        
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * ((double)(width) / height);

        auto viewport_x = Vector3(viewport_width, 0, 0);
        auto viewport_y = Vector3(0, -viewport_height, 0);

        px_delta_x = viewport_x / width;
        px_delta_y = viewport_y / height;

        auto viewport_upper_left = camera_center - Vector3(0, 0, focal_length) - viewport_x / 2 - viewport_y / 2;
        px00_loc = viewport_upper_left + 0.5 * (px_delta_x + px_delta_y);
    }

    void render(const ObjectList &world) {
        std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
        for (int j = 0; j < height; ++j) {
            std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
            for (int i = 0; i < width; ++i) {
                Color px_color(0,0,0);
                for (int sample = 0; sample < samples_per_px; ++sample) {
                    Ray r = get_ray(i, j);
                    px_color += ray_color(r, world);
                }
                write_color(std::cout, px_color * px_samples_scale);
            }
        }
        std::clog << "\rDone.                 \n";
    }

private:
    Color ray_color(const Ray &r, const ObjectList &world) const {
        HitRecord rec;
        if (world.hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + Color_White);
        }

        Vector3 unit_dir = unit_vector(r.direction());
        auto a = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - a) * Color_White + a * Color_Sky;
    }

    Ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto px_sample = px00_loc + ((i+offset.x()) * px_delta_x) + ((j+offset.y()) * px_delta_y);
        auto ray_origin = camera_center;
        auto ray_dir = px_sample - ray_origin;
        return Ray(ray_origin, ray_dir);
    }

    Vector3 sample_square() const {
        return Vector3(random_double() - 0.5, random_double() -0.5, 0);
    }
};

#endif /* CAMERA_H */
