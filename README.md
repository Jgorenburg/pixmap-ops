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

TODO: Document the features of your PPM image class here. Include example images.
![Original](/images/image.jpg)



Rotate:

Rotate takes an angle and a pair of coordinates and returns a copy of the original image rotated around the coordinates. If the new image is diagonal, black pixels will fill in the empty pixels to make a rectangle.



Invert:

Invert performs the operation I' = 255 - I on every pixel in the image and returns a new image.




Channelshift:

Channelshift shifts the rgb values of each pixel so that r' = b, b' = g, and g' = r, then returns a new image.


Lighten:

There are two lighten functions - lightenblend and lightenabsolute - both of which take another image of equal dimensions as an argument. Lightenblend takes the lightest r, b, and g values between each image for each pixel and uses those new values in the resulting image. Lightenabsolute compares pixels in the same place at takes the one with the lower cumulative rgb value for the new image.


Boxblur:  

Boxblur applies a boxblur on the image by making each pixel's color the average of its surrounding pixels and then returning the new image.

![Boxblurred](/images/boxblur.jpg)

Equalize:

Equalize tries to level out the colors in an image. It adds up the cumulative r, g, and b values in the entire image, finds the middle value, and then creates a ratio for each color. Every rgb value is then multiplied by this ratio, so the least prevalent color's values is increased, the middle is unaffected, and the most is decreased.





## Results

TODO: Show artworks using your class
