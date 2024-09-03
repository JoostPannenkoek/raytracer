#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

/**
 * Constructs rays and fires them into the scene and constructs a rendered image based on them.
 */
class camera {
   public:
      // public camera parameters
      double aspectRatio = 1.0;
      int imageWidth = 100;
      int samplesPerPixel = 10;
      int maxDepth = 10;

      void render(const hittable& world) {
         // init the camera
         initialize();

         ofstream image;
         image.open("image.ppm");

         image << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

         // iterate over the column
         for (int j=0; j < imageHeight; j++){
            // indicator
            std::cout << "\rScanlines remaining: " << (imageHeight-j-1) << ' ' << flush;
            // iterate over the row
            for (int i=0; i < imageWidth; i++){
               color pixelColor(0,0,0);
               for (int sample = 0; sample < samplesPerPixel; sample++) {
                  ray r = get_ray(i,j);
                  pixelColor += ray_color(r, maxDepth, world);
               }
               write_color(image, pixelColor*pixelSamplesScale);
            }
         }
         image.close();
         std::cout << "\n Image succesfully created.\n";
      }

   private:
      // private camera variables here
      int imageHeight;
      double pixelSamplesScale;
      point3 cameraCenter;
      point3 pixelZeroPos;
      vec3 pixelDeltaU;
      vec3 pixelDeltaV;


      void initialize() {
         // calculate image height
         imageHeight = int(imageWidth / aspectRatio);
         imageHeight = (imageHeight < 1) ? 1 : imageHeight;

         // calculate sampling scale
         pixelSamplesScale = 1.0/samplesPerPixel;

         // define the camera
         auto focalLength = 1.0;
         auto viewportHeight = 2.0;
         auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);

         // calculate vectors along the horizontal and vertical parts of the viewport
         auto viewportU = vec3(viewportWidth, 0,0);
         auto viewportV = vec3(0, -viewportHeight, 0);

         // calculate the horizontal and vertical delta vectors from pixel to pixel
         pixelDeltaU = viewportU/imageWidth;
         pixelDeltaV = viewportV/imageHeight;

         // calculate the location of the upper left pixel
         auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLength) - viewportU/2 - viewportV/2;
         pixelZeroPos = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
      }

      color ray_color(const ray& r, int depth, const hittable& world) const {
         // If we've exceeded the ray bounce limit, no more light is gathered.
         if (depth <= 0)
            return color(0,0,0);

         hit_record rec;

         if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered)) {
               color next = ray_color(scattered, depth-1, world);
               return attenuation * next;
            }
            return color(0,0,0);
         }

         color blue(0.5, 0.7, 1.0);
         vec3 unitDir = unit_vector(r.direction());
         auto a = 0.5 * (unitDir.y() + 1.0);
         return (1.0-a) * color(1.0, 1.0, 1.0) + a*blue;
      } 

      vec3 sample_square() const {
         // returns a random vec3 in the range x, y in [-0,5, 0.5]
         return vec3(random_double() - 0.5, random_double() - 0.5, 0);
      }

      ray get_ray(int i, int j) {
         auto offset = sample_square();
         auto pixelSample = pixelZeroPos + 
            ((i+offset.x())*pixelDeltaU) + 
            ((j+offset.y())*pixelDeltaV);
         auto rayDir = pixelSample - cameraCenter;
         ray r(cameraCenter, rayDir);
         return r;
      }
};

#endif