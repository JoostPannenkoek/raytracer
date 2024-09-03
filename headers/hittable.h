#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material;

class hit_record {
   public:
      point3 p;
      vec3 normal;
      shared_ptr<material> mat;
      double t;
      bool frontFacing;

      void set_face_normal(const ray& r, const vec3& outwardNormal) {
         // sets the hit record normal vector
         // it is assumed that outward_normal is of unit length

         frontFacing = dot(r.direction(), outwardNormal) < 0;
         normal = frontFacing ? outwardNormal : -outwardNormal;
      }
};

class hittable {
   public:
      virtual ~hittable() = default;

      virtual bool hit(const ray& r, interval rayT, hit_record& rec) const = 0;
};

#endif