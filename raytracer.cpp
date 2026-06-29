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

int main(int argc, char const *argv[])
{
    // World
    ObjectList world;
    for (auto [p, r, m]: spheres) world.add(make_shared<Sphere>(p, r, m));
    
    Camera camera;
    camera.render(world);

    return 0;
}
