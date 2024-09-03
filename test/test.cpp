#include <iostream>
#include <fstream>

#include "headers/color.h"
#include "headers/ray.h"
#include "headers/vec3.h"

using namespace std;


void test() {
   int width = 256;
   int height = 256;

   ofstream image;
   image.open("image.ppm");

   image << "P3\n" << width << ' ' << height << "\n255\n";

   // iterate over the column
   for (int j=0; j < height; j++){
      // indicator
      cout << "\rScanlines remaining: " << (height-j-1) << ' ' << std::flush;
      // iterate over the row
      for (int i=0; i < width; i++){
         double r = (double)i / (width-1);
         double g = (double)j / (height-1);
         double b = 1-((r+g)/2);
   
         auto pixelColor = color(r,g,b);
         write_color(image, pixelColor);
      }
   }
   image.close();
   cout << "\n Image succesfully created.\n";
}