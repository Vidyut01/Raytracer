#include "raytracer.h"

#include "object.h"
#include "object_list.h"
#include "sphere.h"
#include "camera.h"

// tmp arr, the numbers were confusing
const std::pair<Point3, double> spheres[] = {
    {Point3(0,0,-1), 0.5},
    {Point3(0,-100.5, -1), 100},
    {Point3(1, 50, -150), 100}
};

int main(int argc, char const *argv[])
{
    // World
    ObjectList world;
    for (auto [p, r]: spheres) world.add(make_shared<Sphere>(p, r));
    
    Camera camera;
    camera.render(world);

    return 0;
}
