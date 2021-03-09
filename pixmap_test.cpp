#include <iostream>
#include <math.h>
#include "ppm_image.h"
using namespace std;
using namespace agl;

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC //to get more details
#endif


void otherFunct()
{
	ppm_image test;
	test.load("../images/feep.ppm");
	test = test.subimage(0, 0, 1, 2);
}

int main(int argc, char** argv)
{
	ppm_image image;
	ppm_image final;
	image.load("../images/image.ppm");

	/*final = image.rotate(45, 0, 0);
	final.save("../images/rotate.ppm");

	final = image.invert();
	final.save("../images/invert.ppm");

	final = image.channelShift();
	final.save("../images/channelShift.ppm");

	ppm_image earth;
	earth.load("../images/earth-ascii.ppm");
	earth = earth.resize(image.width(), image.height());
	final = image.lightestabsolute(earth);
	final.save("../images/lightabs.ppm");
	final = image.lightestblend(earth);
	final.save("../images/lightblend.ppm");

	final = image.boxblur();
	final.save("../images/boxblur.ppm");
	*/
	final = image.equalize();
	final.save("../images/equalize.ppm");





	
	return 0;

	/*
	ppm_image image;
	ppm_image grey;
	ppm_image inverted;
	ppm_image channelshifted1;
	ppm_image channelshifted2;
	ppm_image boxblur;
	ppm_image lightengrey;
	ppm_image lighten;
	


	cout << "opening image\n";
	image.load("../images/image2.ppm");
	cout << "image loaded\n";

	grey = image.grayscale();
	cout << "greyscale\n";
	inverted = image.invert();
	cout << "inverted\n";
	channelshifted1 = image.channelShift();
	channelshifted2 = channelshifted1.channelShift().equalize();
	cout << "channel blended\n";

	boxblur = image.boxblur();

	cout << "lightened\n";
	lightengrey = grey.gammaCorrect(0.965f);
	lighten = image.lightestabsolute(lightengrey);




	
	int wstep = max(1, image.width() / 50);
	int hstep = max(1, image.height() / 50);

	// the max distance at which an image is still included
	// dist from a corner to the middle
	float maxdist = sqrtf(pow(image.width(), 2) + pow(image.height(), 2)) / 2;

	ppm_image final(image.height(), image.width());
	ppm_image base;
	ppm_image channelshifted1h;
	ppm_image invertedh;
	ppm_image boxblurh;
	ppm_image lightenh;

	cout << "entering for loop\n";
	
	for (int i = 0; i < image.height(); i = i + hstep) {

		for (int j = 0; j < image.width(); j = j + wstep) {

			// accounts for rounding problems
			if (j + wstep > image.width()) {
				wstep = image.width() - j;
			}
			if (i + hstep > image.height()) {
				hstep = image.height() - i;
			}

			base = final.subimage(j, i, wstep, hstep);
			
			
			channelshifted1h = channelshifted1.subimage(j, i, wstep, hstep);
			float ch_dist = sqrtf(pow(j, 2) + pow(i, 2));
			float ch_alpha = min(1.0f, ch_dist / maxdist);

			invertedh = inverted.subimage(j, i, wstep, hstep);
			float inv_dist = sqrtf(pow(image.width() - j, 2) + pow(image.height() - i, 2));
			float inv_alpha = min(1.0f, inv_dist / maxdist);

			
			boxblurh = boxblur.subimage(j, i, wstep, hstep);
			float bb_dist = sqrtf(pow(j, 2) + pow(image.height() - i, 2));
			float bb_alpha = min(1.0f, bb_dist / maxdist);

			lightenh = lighten.subimage(j, i, wstep, hstep);
			float l_dist = sqrtf(pow(image.width() - j, 2) + pow(i, 2));
			float l_alpha = min(1.0f, l_dist / maxdist);


			base = base.alpha_blend(channelshifted1h, ch_alpha);
			base = base.alpha_blend(invertedh, inv_alpha);
			base = base.alpha_blend(boxblurh, bb_alpha);
			base = base.alpha_blend(lightenh, l_alpha);


			final.replace(base, j, i);

		}

	}

	
	final.save("../images/newimage3.ppm");
	
	return 0;
	*/





	/*
	ppm_image image(10, 20);

	ppm_image image2(image);

	ppm_image image3(30, 2);

	image2 = image3;

	image2.load("../images/feep.ppm");

	image2.save("../images/duck.ppm");
	image3.load("../images/duck.ppm");
	ppm_pixel newpix = image3.get(3, 3);
	cout << newpix.r << " " << newpix.g << " " << newpix.b << endl;
	image3.set(0, 0, newpix);
	image3.save("../images/duck.ppm");

	image3.load("../images/earth-ascii.ppm");
	ppm_image image4 = image3.equalize();
	image4.save("../images/equalize.ppm");
	*/
  

   /*
   image.load("../images/feep.ppm");
   image.save("feep-test-save.ppm"); // should match original
   
   // should print 4 4
   cout << "loaded feep: " << image.width() << " " << image.height() << endl;

   // test: copy constructor
   ppm_image copy = image; 
   copy.save("feep-test-copy.ppm"); // should match original and load into gimp

   // test: assignment operator
   copy = image; 
   copy.save("feep-test-assignment.ppm"); // should match original and load into gimp

   // should print r,g,b
   ppm_pixel pixel = image.get(1, 1);
   cout << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << endl;

   // test: setting a color
   pixel.r = 255;
   image.set(1, 1, pixel);
   image.save("feep-test-newcolor.ppm");

   // test a non-trivial image
   image.load("../images/earth-ascii.ppm"); // a real image

   // should print 400 400
   cout << "loaded earth: " << image.width() << " " << image.height() << endl;

   // resize
   ppm_image resize = image.resize(200,300);
   resize.save("earth-200-300.ppm");

   // grayscale
   ppm_image grayscale = image.grayscale(); 
   grayscale.save("earth-grayscale.ppm");

   // flip horizontal
   ppm_image flip = image.flip_horizontal(); 
   flip.save("earth-flip.ppm"); 

   // sub image
   ppm_image sub = image.subimage(200, 200, 100, 100); 
   sub.save("earth-subimage.ppm"); 

   // gamma correction
   ppm_image gamma = image.gammaCorrect(0.6f); 
   gamma.save("earth-gamma-0.6.ppm"); 

   gamma = image.gammaCorrect(2.2f);
   gamma.save("earth-gamma-2.2.ppm"); 

   // alpha blend
   ppm_image soup;
   soup.load("../images/soup-ascii.ppm");

   int y = (int) (0.5f * (image.width() - soup.width()));
   int x = (int) (0.5f * (image.height() - soup.height()));
   ppm_image background = image.subimage(x, y, soup.width(), soup.height());
   background.save("background-test.ppm");
   ppm_image blend = background.alpha_blend(soup, 0.5f);
   image.replace(blend, x, y);
   image.save("earth-blend-0.5.ppm");
   */
}

