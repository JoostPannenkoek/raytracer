
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
   auto center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
   auto left = make_shared<metal>(color(0.8, 0.8, 0.0));
   auto right = make_shared<metal>(color(0.8, 0.1, 0.1));

   world.add(make_shared<sphere>(point3(0, 0, -1.2), 0.5, center));
   world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, ground));
   world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, left));
   world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, right));

   // camera
   camera cam;
   
   cam.aspectRatio = 16.0 / 9.0;
   cam.imageWidth = 400;
   cam.samplesPerPixel = 100;
   cam.maxDepth = 50;

   cam.render(world);
}