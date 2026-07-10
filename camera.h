#ifndef CAMERA_H
#define CAMERA_H

#include "object_list.h"
#include "material.h"

class Camera {
public:
    double aspect_ratio = 16.0 / 9.0;
    int width = 400;
    int samples_per_px = 100;
    int max_depth = 50;
    
    double vfov = 90;
    Point3 lookfrom = Point3(0,0,0);
    Point3 lookat = Point3(0,0,-1);
    Vector3 vup = Vector3(0,1,0);

    double defocus_angle = 0;
    double focus_dist = 10;

private:
    double px_samples_scale;
    int height;
    Point3 px00_loc, px_delta_x, px_delta_y, camera_center;
    Vector3 x, y, z;

    Vector3 defocus_disk_x;
    Vector3 defocus_disk_y;


public:
    void render(const ObjectList &world) {
        init();

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
    Color ray_color(const Ray &r, const ObjectList &world, int depth = 0) const {
        if (depth > max_depth) return Color(0,0,0);
        HitRecord rec;
        if (world.hit(r, Interval(0.001, infinity), rec)) {
            Ray scattered;
            Color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered)) {
                return attenuation * ray_color(scattered, world, depth + 1);
            }
            return Color(0,0,0);
        }

        Vector3 unit_dir = unit_vector(r.direction());
        auto a = 0.5 * (unit_dir.y() + 1.0);
        return (1.0 - a) * Color_White + a * Color_Sky;
    }

    Ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto px_sample = px00_loc + ((i+offset.x()) * px_delta_x) + ((j+offset.y()) * px_delta_y);
        auto ray_origin = defocus_angle <= 0 ? camera_center : defocus_disk_sample();
        auto ray_dir = px_sample - ray_origin;
        return Ray(ray_origin, ray_dir);
    }

    Vector3 sample_square() const {
        return Vector3(random_double() - 0.5, random_double() -0.5, 0);
    }

    Point3 defocus_disk_sample() const {
        auto p = random_in_unit_disk();
        return camera_center + (p[0] * defocus_disk_x) + (p[1] * defocus_disk_y);
    }
    void init() {
        height = (height = width / aspect_ratio) >= 1 ? height : 1;
        
        px_samples_scale = 1.0 / samples_per_px;
        
        camera_center = lookfrom;

        auto theta = degrees_to_radians(vfov);
        auto h = std::tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * ((double)(width) / height);

        z = unit_vector(lookfrom - lookat);
        x = unit_vector(cross(vup, z));
        y = cross(z, x);

        auto viewport_x = viewport_width * x;
        auto viewport_y = viewport_height * -y;

        px_delta_x = viewport_x / width;
        px_delta_y = viewport_y / height;

        auto viewport_upper_left = camera_center - (focus_dist * z) - viewport_x / 2 - viewport_y / 2;
        px00_loc = viewport_upper_left + 0.5 * (px_delta_x + px_delta_y);

        auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_x = x * defocus_radius;
        defocus_disk_y = y * defocus_radius;
    }
};

#endif /* CAMERA_H */
