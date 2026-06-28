#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "object.h"
#include "raytracer.h"

#include <vector>

class ObjectList : public Object {
public:
    std::vector<shared_ptr<Object>> objects;

    ObjectList() {}
    ObjectList(shared_ptr<Object> obj) { add(obj); }

    void clear() { objects.clear(); };

    void add(shared_ptr<Object> obj) {
        objects.push_back(obj);
    }

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &obj: objects) {
            if (obj->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        
        return hit_anything;
    }
};

#endif /* OBJECT_LIST_H */
