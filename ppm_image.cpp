#define _USE_MATH_DEFINES

#include "ppm_image.h"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include <list>

using namespace agl;
using namespace std;

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC //to get more details
#endif

ppm_image::ppm_image() 
{
}

ppm_image::ppm_image(int height, int width) 
{
    h = height;
    w = width;

    data2D = new ppm_pixel* [h];
    for (int i = 0; i < h; i++)
    {
        data2D[i] = new ppm_pixel[w];
        for (int j = 0; j < w; j++)
        {
            ppm_pixel idx{0, 0, 0};
            data2D[i][j] = idx;
        }
    }
}

ppm_image::ppm_image(const ppm_image& orig)
{
    h = orig.height();
    w = orig.width();

    data2D = new ppm_pixel * [h];
    for (int i = 0; i < h; i++)
    {
        data2D[i] = new ppm_pixel[w];
        for (int j = 0; j < w; j++)
        {
            ppm_pixel idx;
            idx.r = orig.data2D[i][j].r;
            idx.g = orig.data2D[i][j].g;
            idx.b = orig.data2D[i][j].b;
            data2D[i][j] = idx;
        }
    }
}

ppm_image& ppm_image::operator=(const ppm_image& orig)
{

   if (&orig == this) // protect against self-assignment
   {
      return *this;
   }

   // todo: your code here
   for (int i = 0; i < h; i++)
   {
       delete[] data2D[i];
   }
   delete[] data2D;

   h = orig.height();
   w = orig.width();

   data2D = new ppm_pixel* [h];
   for (int i = 0; i < h; i++)
   {
       data2D[i] = new ppm_pixel[w];
       for (int j = 0; j < w; j++)
       {
           ppm_pixel idx;
           idx.r = orig.data2D[i][j].r;
           idx.g = orig.data2D[i][j].g;
           idx.b = orig.data2D[i][j].b;
           data2D[i][j] = idx;
       }
   } 

   return *this;   
}

ppm_image::~ppm_image()
{
    for (int i = 0; i < h; i++)
    {
        delete[] data2D[i];
    }
    delete[] data2D;
    
}

bool ppm_image::load(const std::string& filename)
{
    ifstream image(filename);
    if (!image) {
        cout << "cannot load image: " << filename << endl;
        return false;
    } else {
        for (int i = 0; i < h; i++)
        {
            delete[] data2D[i];
        }

        string format;
        int maxVal;
        image >> format;
        image >> w;
        image >> h;
        image >> maxVal;
        if (format != "P3" || maxVal != 255) {
            cout << "header error: format should be P3 and the max value 255\n";
            cout << "instead format: " << format << " and the max value is: " << maxVal << endl;
            return false;
        } else {
            delete[] data2D;
            data2D = new ppm_pixel * [h];
            for (int i = 0; i < h; i++) {

                data2D[i] = new ppm_pixel[w];
                for (int j = 0; j < w; j++) {

                    ppm_pixel idx;
                    image >> idx.r;
                    image >> idx.g;
                    image >> idx.b;
                    data2D[i][j] = idx;

                }
            }
            return true;
        }
    } 
}

bool ppm_image::save(const std::string& filename) const
{
    fstream image;
    image.open(filename, ios::out);

    if (!image) {
        cout << "file not created\n";
        return false;
    }
    else {
        image << "P3" << endl;
        image << w << " ";
        image << h << endl;
        image << 255 << endl;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                image << data2D[i][j].r << " ";
                image << data2D[i][j].g << " ";
                image << data2D[i][j].b << " ";
            }
            image << endl;
        }

        return true;
    }
}

ppm_image ppm_image::resize(int width, int height) const
{
    ppm_image result(height, width);
    
    float rowScale = (h - 1.0f) / (height - 1.0f);
    float colScale = (w - 1.0f) / (width - 1.0f);
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            int row = floor(rowScale * i);
            int col = floor(colScale * j);

            result.data2D[i][j] = data2D[row][col];
        }
    }
    return result;
}

ppm_image ppm_image::flip_horizontal() const
{
    ppm_image flippedImage(h, w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            flippedImage.data2D[i][j] = data2D[h - 1 - i][j];
        }
    }
    return flippedImage;
}

ppm_image ppm_image::subimage(int startx, int starty, int width, int height) const
{

    if (startx < 0 || startx > w - width) {
        cerr << "error: startx " << startx << " is invalid\n";

        return ppm_image();
    } 
    else if (starty < 0 || starty > h - height) {
        cerr << "error: starty " << starty << " is invalid\n";
        return ppm_image();
    }


    ppm_image result(height, width);
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {

            result.data2D[i][j] = data2D[i + starty][j + startx];
        }
    }

    return result;
}

void ppm_image::replace(const ppm_image& image, int startx, int starty)
{

    if (startx < 0) {
        cerr << "error: startx " << startx << " is invalid\n";
    }
    else if (starty < 0) {
        cerr << "error: starty " << starty << " is invalid\n";
    }
    else {

        ppm_image placeholder = *this;

        for (int i = 0; i < h; i++)
        {
            delete[] data2D[i];
        }
        delete[] data2D;

        w = max(w, image.width() + startx);
        h = max(h, image.height() + starty);



        data2D = new ppm_pixel * [h];

        for (int i = 0; i < h; i++) {

            data2D[i] = new ppm_pixel[w];
            for (int j = 0; j < w; j++) {

                // checks if the current [i, j] is in the replaced area
                // replaces it if it is
                if (i >= starty && i < starty + image.height() && j >= startx && j < startx + image.width()) {
                    data2D[i][j] = image.data2D[i - starty][j - startx];
                }
                // checks if were out of the original image
                // adds black pixel if we are
                else if (i >= placeholder.height() || j >= placeholder.width()) {
                    data2D[i][j] = ppm_pixel{ 0, 0, 0 };
                }
                // finally, just adds original pixel
                else {
                    data2D[i][j] = placeholder.data2D[i][j];
                }
            }
        }

    }

}

ppm_image ppm_image::alpha_blend(const ppm_image& other, float alpha) const
{
    if (alpha < 0 || alpha > 1) {
        cerr << "error: alpha must be between 0 and 1\n";
        cerr << "instead, alpha is: " << alpha << endl;
        return ppm_image();
    }
    if (height() != other.height() || width() != other.width()) {
        cerr << "error, the images do not have the same dimensions\n";
        return ppm_image();
    }

    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {

            
            int r = data2D[i][j].r * alpha + other.data2D[i][j].r * (1.0f - alpha);
            r = min(255, r);
            int g = data2D[i][j].g * alpha + other.data2D[i][j].g * (1.0f - alpha);
            g = min(255, g);
            int b = data2D[i][j].b * alpha + other.data2D[i][j].b * (1.0f - alpha);
            b = min(255, b);

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }
    return result;
}

ppm_image ppm_image::gammaCorrect(float gamma) const
{
    if (gamma <= 0) {
        cerr << "error: gamma must be greater than 0\n";
        cerr << "instead, gamma is: " << gamma << endl;
        return ppm_image();
    }

    ppm_image result(*this);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {

            float gam = 1.0f / gamma;
            float scaledR = data2D[i][j].r / 255.0f;
            float scaledG = data2D[i][j].g / 255.0f;
            float scaledB = data2D[i][j].b / 255.0f;
            int r = pow(scaledR, gam) * 255.0f;
            r = min(r, 255);
            int g = pow(scaledG, gam) * 255.0f;
            g = min(g, 255);
            int b = pow(scaledB, gam) * 255.0f;
            b = min(b, 255);

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }
    return result;
}

ppm_image ppm_image::grayscale() const
{
   ppm_image result(*this);
   for (int i = 0; i < h; i++) {

       for (int j = 0; j < w; j++) {

           int c = (0.3f * data2D[i][j].r) + (0.59f * data2D[i][j].g) + (0.11f * data2D[i][j].b);
           result.data2D[i][j] = ppm_pixel{ c, c, c };
       }
   }
   return result;
}

ppm_pixel ppm_image::get(int row, int col) const
{
    if (row < h && col < w) {
        return data2D[row][col];
    }
    else {
        cerr << "error: pos " << row << ", " << col << " does not exist \n";
        ppm_pixel errorPixel{ -1, -1, -1 };
        return errorPixel;
    }
}

void ppm_image::set(int row, int col, const ppm_pixel& c)
{
    if (row < h && col < w) {
        data2D[row][col] = c;
    }
    else {
        cerr << "error: pos " << row << ", " << col << " does not exist \n";
    }
}

int ppm_image::height() const
{
   return h;
}

int ppm_image::width() const
{
   return w;
}

ppm_image ppm_image::rotate(float angle, int x, int y) const {

    float rangle = angle * M_PI / 180;

    // checks to make sure x and y are inside the image
    if (x < 0 || x >= w) {
        cerr << "error: improper x coordinate: " << x << endl;
        return ppm_image();
    }
    if (y < 0 || y >= h) {
        cerr << "error: improper y coordinate: " << y << endl;
        return ppm_image();
    }

    // new position of the four corners
    list <int> c1 = findRotatedCoord(rangle, x, y, 0, 0);
    list <int> c2 = findRotatedCoord(rangle, x, y, w - 1, 0);
    list <int> c3 = findRotatedCoord(rangle, x, y, w - 1, h - 1);
    list <int> c4 = findRotatedCoord(rangle, x, y, 0, h - 1);

    int leastw = min(min(c1.front(), c2.front()), min(c3.front(), c4.front()));
    int mostw = max(max(c1.front(), c2.front()), max(c3.front(), c4.front()));
    int neww = mostw - leastw;
    

    int leasth = min(min(c1.back(), c2.back()), min(c3.back(), c4.back()));
    int mosth = max(max(c1.back(), c2.back()), max(c3.back(), c4.back()));
    int newh = mosth - leasth;
   
   
    ppm_image result(newh, neww);

    for (int i = leasth; i < mosth; i++) {

        for (int j = leastw; j < mostw; j++) {

            list <int> oldCoords = findRotatedCoord(-1 * rangle, x, y, j, i);
            int oldx = oldCoords.front();
            int oldy = oldCoords.back();
            if (oldx < 0 || oldx >= w || oldy < 0 || oldy >= h) {
                result.data2D[i - leasth][j - leastw] = ppm_pixel{ 0,0,0 };
            }
            else {
                result.data2D[i - leasth][j - leastw] = data2D[oldCoords.back()][oldCoords.front()];
            }
        }
    }
    return result;
    
}

list <int> ppm_image::findRotatedCoord(float angle, int xpos, int ypos, int cx, int cy) const {

    // the formula for the new position
    int xnew = cos(angle) * (cx - xpos) - sin(angle) * (cy - ypos) + xpos;
    int ynew = sin(angle) * (cx - xpos) + cos(angle) * (cy - ypos) + ypos;
    list <int> results = { xnew, ynew };
    return results;
}

ppm_image ppm_image::invert() const {

    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {

            
            int r = 255 - data2D[i][j].r;
            int g = 255 - data2D[i][j].g;
            int b = 255 - data2D[i][j].b;

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }
    return result;
}

ppm_image ppm_image::channelShift() const {

    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {


            int r = data2D[i][j].b;
            int g = data2D[i][j].r;
            int b = data2D[i][j].g;

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }
    return result;
}

ppm_image ppm_image::lightestblend(const ppm_image& other) const {

    if (h != other.height() || w != other.width()) {
        cerr << "error: images do not have the same dimensions\n";
        return ppm_image();
    }

    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        
        for (int j = 0; j < w; j++) {


            int r = max(data2D[i][j].r, other.data2D[i][j].r);
            int g = max(data2D[i][j].g, other.data2D[i][j].g);
            int b = max(data2D[i][j].b, other.data2D[i][j].b);

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }
    return result;
}

ppm_image ppm_image::lightestabsolute(const ppm_image& other) const {

    if (h != other.height() || w != other.width()) {
        cerr << "error: images do not have the same dimensions\n";
        return ppm_image();
    }

    ppm_image result(h, w);
    
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {


            int thisSum = data2D[i][j].r + data2D[i][j].g + data2D[i][j].b;
            int otherSum = other.data2D[i][j].r + other.data2D[i][j].g + other.data2D[i][j].b;
           
            if (thisSum > otherSum) {
                result.data2D[i][j] = data2D[i][j];
            }
            else {
                result.data2D[i][j] = other.data2D[i][j];
            }
           }
    }
    return result;
}

ppm_image ppm_image::boxblur() const {

    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {
           
            int r = 0;
            int g = 0;
            int b = 0;
            int count = 0;

            for (int k = i - 1; k < i + 2; k++) {
                for (int l = j - 1; l < j + 2; l++) {
                    if (k >= 0 && k < h && l >= 0 && l < w) {
                        count++;
                        r = r + data2D[k][l].r;
                        g = g + data2D[k][l].g;
                        b = b + data2D[k][l].b;

                    }
                }
            }

            r = r / count;
            g = g / count;
            b = b / count;
           
            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }

    return result;
}

ppm_image ppm_image::equalize() const {

    // finding mult ratio for each color
    float sumR = 0;
    float sumG = 0;
    float sumB = 0;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            sumR = sumR + data2D[i][j].r;
            sumG = sumG + data2D[i][j].g;
            sumB = sumB + data2D[i][j].b;
        }
    }

    float middle;
    if (sumR > sumG) {
        if (sumG > sumB)        { middle = sumG; }
        else if (sumR > sumB)   { middle = sumB; }
        else                    { middle = sumR; }
    }
    else {
        if (sumR > sumB)        { middle = sumR; }
        else if (sumG > sumB)   { middle = sumB; }
        else                    { middle = sumG; }
    }
    
 
    float rRatio = 1;
    float gRatio = 1;
    float bRatio = 1;

    if (sumR != 0) { rRatio = middle / sumR; }
    if (sumG != 0) { gRatio = middle / sumG; }
    if (sumB != 0) { bRatio = middle / sumB; }


    // multiply all rbg values by their ratio
    ppm_image result(h, w);
    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++) {

            int r = data2D[i][j].r * rRatio;
            r = min(255, r);
            int g = data2D[i][j].g * gRatio;
            g = min(255, g);
            int b = data2D[i][j].b * bRatio;
            b = min(255, b);

            result.data2D[i][j] = ppm_pixel{ r, g, b };
        }
    }

    cout << sumR << " " << sumG << " " << sumB << endl;
    cout << rRatio << " " << gRatio << " " << bRatio << endl;

    return result;
}