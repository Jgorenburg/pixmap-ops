#include <iostream>
#include <math.h>
#include "ppm_image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
	ppm_image image;
	ppm_image grey;
	ppm_image inverted;
	ppm_image channelshifted1;
	ppm_image channelshifted2;
	ppm_image boxblur;
	ppm_image lightengrey;
	ppm_image lighten;
	ppm_image final;

	image.load("../images/image.ppm");

	final = image.rotate(45, 0, 0);
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

	final = image.equalize();
	final.save("../images/equalize.ppm");





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


	final.save("../images/goat.ppm");

	return 0;
}

