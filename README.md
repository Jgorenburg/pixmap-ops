# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 16 2019" ..
pixmap-ops/build $ start Pixmap-Ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell,

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators

Original Image
![Original1](/images/image.jpg)



Rotate:

Rotate takes an angle in degrees and a pair of coordinates and returns a copy of the original image rotated around the coordinates. If the new image is diagonal, black pixels will fill in the empty pixels to make a rectangle.

Rotated 45 degrees
![Rotated 45 degrees](/images/rotate.jpg)


Invert:

Invert performs the operation I' = 255 - I on every pixel in the image and returns a new image.

Inverted
![Inverted](/images/invert.jpg)


Channelshift:

Channelshift shifts the rgb values of each pixel so that r' = b, b' = g, and g' = r, then returns a new image.

Channelshifted
![Channelshifted](/images/channelShift.jpg)


Lighten:

There are two lighten functions - lightenblend and lightenabsolute - both of which take another image of equal dimensions as an argument. Lightenblend takes the lightest r, b, and g values between each image for each pixel and uses those new values in the resulting image. Lightenabsolute compares pixels in the same place at takes the one with the lower cumulative rgb value for the new image.

Lighten Blend
![Lighten Blend](/images/lightblend.jpg)

Lighten Absolute
![Lighten Absolute](/images/lightabs.jpg)


Boxblur:  

Boxblur applies a boxblur on the image by making each pixel's color the average of its surrounding pixels and then returning the new image.

Boxblurred
![Boxblurred](/images/boxblur.jpg)


Equalize:

Equalize tries to level out the colors in an image. It adds up the cumulative r, g, and b values in the entire image, finds the middle value, and then creates a ratio for each color. Every rgb value is then multiplied by this ratio, so the least prevalent color's values is increased, the middle is unaffected, and the most is decreased.

Equalized
![Equalized](/images/equalize.jpg)

There's more blue and less green in this image



## Results

These images were made by taking four of the above effects - boxblur, invert, channelshift, and lightenabs on a greyscale version - on each image. Each effect was centered at a distinct corner and its opacity decreases in pixels farther from that corner. 

First Image
![First](/images/final1.jpg)
I first did it with a 20x20 grid, each with different opacity combonations.

Second Image
![Second](/images/final2.jpg)
This one uses a 50x50 grid. It's looks much more like a gradiant than the first.

Third Image
![Third](/images/final3.jpg)
I tried this on another image as well.
