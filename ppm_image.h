//----------------------------------------
// PPM image class
// Author: Bryn Mawr College Basecode 2021
//----------------------------------------

#pragma once
#include <string>
#include <list>

namespace agl
{
  struct ppm_pixel
  {
     int r;
     int g;
     int b;
  };

  class ppm_image
  {

  public:
     ppm_image();
     ppm_image(int height, int width);
     ppm_image(const ppm_image& orig);
     ppm_image& operator=(const ppm_image& orig);

     virtual ~ppm_image();

     // load the given filename
     // returns true if the load is successful; false otherwise
     bool load(const std::string& filename);

     // save the given filename
     // returns true if the save is successful; false otherwise
     bool save(const std::string& filename) const;

     // Returns a copy of this image resized to the given width and height
     ppm_image resize(int width, int height) const;

     // Return a copy of this image flipped around the horizontal midline
     ppm_image flip_horizontal() const;

     // Return a sub-image having the given top,left coordinate and (width, height)
     ppm_image subimage(int x, int y, int width, int height) const;

     // Replace the portion starting at (row, col) with the given image
     // Clamps the image if it doesn't fit on this image
     void replace(const ppm_image& image, int x, int y);

     // Return a copy of this image with the given gamma correction applied to it
     ppm_image gammaCorrect(float gamma) const;

     // Apply the following calculation to the pixels in 
     // our image and the given image:
     //    this.pixels = this.pixels * (1-alpha) + other.pixel * alpha
     // Can assume that the two images are the same size
     ppm_image alpha_blend(const ppm_image& other, float amount) const;

     // Return a copy of this image converted to grayscale
     ppm_image grayscale() const;

     // Get the pixel at index (row, col)
     ppm_pixel get(int row, int col) const;

     // Set the pixel at index (row, col)
     void set(int row, int col, const ppm_pixel& c);

     // return the width of this image
     int width() const;

     // return the height of the image
     int height() const;

     // my methods

     // returns image an rotated around point x,y inside the original image
     // takes angle in degrees
     ppm_image rotate(float angle, int x, int y) const;

     // returns an inverted image
     ppm_image invert() const;

     // returns an image with the color channels shifted
     // r -> g -> b
     ppm_image channelShift() const;

     // takes lightest rgb values between images, not lightest overall pixels
     ppm_image lightestblend(const ppm_image& other) const;

     // uses the lighest pixel based on adding up rbg values
     ppm_image lightestabsolute(const ppm_image& other) const;

     // box blur
     ppm_image boxblur() const;

     // brings the overall color ratio close to 1:1:1
     ppm_image equalize() const;

     

  protected:
      int h = 0;
      int w = 0;
      ppm_pixel** data2D = NULL;

      // helper function that finds where the new coordinate is
      // takes angle in radians
      std::list <int> findRotatedCoord(float angle, int xpos, int ypos, int cx, int cy) const;
  };
}
