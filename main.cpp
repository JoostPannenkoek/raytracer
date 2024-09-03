
#include <fstream>

#include "headers/camera.h"
#include "headers/rtweekend.h"
#include "headers/hittable.h"
#include "headers/hittable_list.h"
#include "headers/sphere.h"
#include "headers/material.h"

using namespace std;

color ray_color(const ray& r, const hittable& world);
double hit_sphere(point3& center, double radius, const ray& r);

int main() {
   // world
   hittable_list world;

   auto ground = make_shared<lambertian>(color(0.4, 0.8, 0.2));
   auto rubber = make_shared<lambertian>(color(0.1, 0.2, 0.5));
   auto metal1 = make_shared<metal>(color(0.8, 0.8, 0.0), 0.5);
   auto metal2 = make_shared<metal>(color(0.8, 0.1, 0.1), 0.1);
   auto glass1 = make_shared<glass>(color(1,1,1), 1.5);
   auto air = make_shared<glass>(color(1,1,1), 1.0/1.5);

   world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, rubber));
   world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, ground));
   world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, metal1));
   world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, glass1));
   world.add(make_shared<sphere>(point3(1, 0, -1), 0.4, air));

   // camera
   camera cam;
   
   cam.aspectRatio = 16.0 / 9.0;
   cam.imageWidth = 400;
   cam.samplesPerPixel = 100;
   cam.maxDepth = 50;

   cam.render(world);
}