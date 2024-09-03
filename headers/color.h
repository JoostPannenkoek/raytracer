#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "interval.h"

using namespace std;
using color = vec3;

inline double linear_to_gamma(double linearComponent) {
   if (linearComponent > 0) {
      return sqrt(linearComponent);
   }
   return 0;
}

void write_color(ostream& out, const color& pixel_color) {
   auto r = pixel_color.x();
   auto g = pixel_color.y();
   auto b = pixel_color.z();

   r = linear_to_gamma(r);
   g = linear_to_gamma(g);
   b = linear_to_gamma(b);

   static const interval intensity(0.000, 0.999);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

   out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif