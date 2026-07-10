# Raytracer

A CPU raytracer written in C++ from scratch, following the [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) series.

## Build

```bash
make
```

Output binary is written to `build/raytracer`.

## Run

```bash
./build/raytracer > output.ppm
```

Or use the test target to write to `build/out.ppm`:

```bash
make test
```

Progress is printed to stderr; the PPM image goes to stdout.

## Camera Parameters

Configured in `raytracer.cpp`:

| Parameter         | Description                                      |
|-------------------|--------------------------------------------------|
| `width`           | Image width in pixels                            |
| `aspect_ratio`    | Width / height ratio                             |
| `samples_per_px`  | Anti-aliasing samples per pixel                  |
| `max_depth`       | Maximum ray bounce depth                         |
| `vfov`            | Vertical field of view (degrees)                 |
| `lookfrom`/`lookat` | Camera position and target                     |
| `defocus_angle`   | Lens aperture angle — set to 0 to disable blur   |
| `focus_dist`      | Distance to the plane of perfect focus           |

## Project Structure

- raytracer.cpp     — Entry point; scene setup and camera config
- camera.h          — Camera, ray sampling, and render loop
- material.h        — Lambertian, Metal, Dielectric
- sphere.h          — Sphere geometry and hit testing
- object.h          — Base hittable interface and HitRecord
- object_list.h     — Scene container
- ray.h             — Ray type
- vector3.h         — Vec3 math (dot, cross, reflect, refract, random)
- color.h           — Color utilities and PPM output
- interval.h        — Scalar interval type used in hit testing
- raytracer.h       — Common includes and utilities (random, constants)

## Cleaning

```bash
make clean
```
