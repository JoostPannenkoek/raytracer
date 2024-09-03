#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include "rtweekend.h"
#include <vector>

using std::make_shared;
using std::shared_ptr;
using namespace std;

class hittable_list : public hittable {
   public:
      vector<shared_ptr<hittable>> objects;
      
      hittable_list() {}
      hittable_list(shared_ptr<hittable> object) {
         objects.push_back(object);
      }
      
      void clear() {
         objects.clear();
      }

      void add(shared_ptr<hittable> object) {
         objects.push_back(object);
      }

      bool hit(const ray& r, interval rayT, hit_record& rec) const override {
         hit_record tempRec;
         bool hitObject = false;
         auto closest = rayT.max;

         for (const auto& object : objects) {
            if(object->hit(r, interval(rayT.min, closest), tempRec)) {
               hitObject = true;
               closest = tempRec.t;
               rec = tempRec;
            }
         }
         return hitObject;
      }
};

#endif