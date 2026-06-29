#ifndef MATERIAL_H
#define MATERIAL_H

#include "object.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &r, const HitRecord &rec, Color &attenuation, Ray &scatterd) const {
        return false;
    }
};

class Lambertian : public Material {
public:
    Lambertian(const Color &albedo) : albedo(albedo) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        auto scatter_dir = rec.normal + random_unit_vector();
        if (scatter_dir.near_zero()) scatter_dir = rec.normal;
        scattered = Ray(rec.p, scatter_dir);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

class Metal : public Material {
public:
    Metal(const Color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        Vector3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    Color albedo;
    double fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(double r_index) : r_index(r_index) {}

    bool scatter(const Ray &r_in, const HitRecord &rec, Color &attenuation, Ray &scattered) const override {
        attenuation = Color(1,1,1);
        double ri = rec.front_face ? (1.0/r_index) : r_index;
        Vector3 unit_dir = unit_vector(r_in.direction());
        
        double cos_theta = std::fmin(dot(-unit_dir, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1;
        Vector3 direction;
        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_dir, rec.normal);
        else
            direction = refract(unit_dir, rec.normal, ri);

        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    double r_index;

    static double reflectance(double cosine, double r_index) {
        double r0 = (r0 = (1 - r_index) / (1 + r_index)) * r0;
        return r0 + (1 - r0) * std::pow(1 - cosine, 5);
    }
};

#endif /* MATERIAL_H */
