#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <fstream>


// C++ std usings
using std::make_shared;
using std::shared_ptr;

// constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592653897932385;

// utility

inline double degrees_to_radians(double degrees) {
   return degrees * pi / 180.0;
}

inline double random_double() {
   // returns a double in range [0,1)

   return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
   // returns a random double in [min, max)
   return min + (max-min)*random_double();
}

// common headers

#include "vec3.h"	
#include "ray.h"
#include "color.h"
#include "interval.h"

#endif