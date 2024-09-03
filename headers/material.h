#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class hit_record; // Forward declaration

class material {
   public:
      virtual ~material() = default;

      virtual bool scatter(
         const ray& rIn, const hit_record& rec, color& attenuation, ray& scattered
      ) const {
         return false;
      }
};

class lambertian : public material {
   public:
      lambertian(const color& albedo) : albedo(albedo) {}

      bool scatter(const ray& rIn, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
         auto scatter_direction = rec.normal + random_unit_vector();

         if(scatter_direction.close_to_zero()) {
            scatter_direction = rec.normal;
         }
         
         scattered = ray(rec.p, scatter_direction);
         attenuation = albedo;
         return true;
      }

   private:
      color albedo;
};

class metal : public material {
   public:
      metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

      bool scatter(const ray& rIn, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
         vec3 reflected = reflect(rIn.direction(), rec.normal);
         reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
         scattered = ray(rec.p, reflected);
         attenuation = albedo;
         return (dot(scattered.direction(), rec.normal) > 0);
      }

   private:
      color albedo;
      double fuzz;
};

class glass : public material {
   public:
      glass(color albedo, double refractiveIndex) : albedo(albedo), refractiveIndex(refractiveIndex) {}
      bool scatter(const ray& rIn, const hit_record& rec, color& attenuation, ray& scattered)
      const override {
         attenuation = albedo;
         double etaOverEtaPrime = rec.frontFacing ? (1.0/refractiveIndex) : refractiveIndex;
         vec3 unitDir = unit_vector(rIn.direction());
         double cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
         double sinTheta = sqrt(1.0 - (cosTheta*cosTheta));

         vec3 rOut;
         bool canRefract = sinTheta * etaOverEtaPrime < 1.0;
         if (!canRefract || schliksReflectance(cosTheta, etaOverEtaPrime) > random_double()) {
            rOut = reflect(rIn.direction(), rec.normal);
         } else {
            rOut = refract(unitDir, rec.normal, etaOverEtaPrime);
         }
         
         scattered = ray(rec.p, rOut);
         return true;
      }
   private:
      double refractiveIndex;
      color albedo;

      static double schliksReflectance(double cosTheta, double refractiveIndex) {
         auto r0 = (1-refractiveIndex) / (1+refractiveIndex);
         r0 *= r0;
         return r0 + (1-r0)*pow((1-cosTheta),5);
      }
};

#endif