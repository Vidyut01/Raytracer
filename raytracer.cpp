#include "raytracer.h"

#include "object.h"
#include "object_list.h"
#include "sphere.h"
#include "camera.h"

const auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0));
const auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
const auto material_left = make_shared<Dielectric>(1.50);
const auto material_bubble = make_shared<Dielectric>(1/1.50);
const auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), .9);

// tmp arr, the numbers were confusing
const std::tuple<Point3, double, shared_ptr<Material>> spheres[] = {
    {Point3(0,-100.5,-1), 100, material_ground},
    {Point3(0, 0, -1.2), 0.5, material_center},
    {Point3(-1, 0, -1), 0.5, material_left},
    {Point3(-1, 0, -1), 0.4, material_bubble},
    {Point3(1, 0, -1), 0.5, material_right}
};

void create_random_world(ObjectList &world);
int main(int argc, char const *argv[])
{
    // World
    ObjectList world;
    // for (auto [p, r, m]: spheres) world.add(make_shared<Sphere>(p, r, m));
    // auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    // auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    // auto material_left   = make_shared<Dielectric>(1.50);
    // auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
    // auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    // world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    // world.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    // world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    // world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    // world.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));
    create_random_world(world);

    Camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.width = 1200;
    camera.samples_per_px = 20;
    camera.max_depth = 500;

    camera.vfov = 20;
    camera.lookfrom = Point3(13,2,3);
    camera.lookat = Point3(0,0,0);
    camera.vup = Vector3(0,1,0);

    camera.defocus_angle = 0.6;
    camera.focus_dist = 10.0;

    camera.render(world);

    return 0;
}

void create_random_world(ObjectList &world) {
    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));
}
