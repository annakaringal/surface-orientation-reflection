/*****************************************************************************
 Title:             s3.cpp
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Uses photometric stereo technigues to estimate the surface
                    normal of the object using three different images of the same
                    object under three different known light sources. Draws these
                    normals as lines on the first image of the object.
 Requirements:      - The light source vectors in the input text file are the same
                      as those for the given images, in the same order.
                    - Threshold is an integer >= 0 && <= 255.
                    - Step is an integer >=0 and <= the number of rows or columns 
                    in the image, whichever is smaller.
 Build:             Compile by running 'make s3' in the working directory
 
 Usage:             ./s3 light_sources_vectors.txt object1.img object2.img object3.img step threshold output_img.pgm
 
 Last Modified:     November 14, 2015  
 *****************************************************************************/

#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "pgm/Image.h"
#include "Validation.h"
#include "Matrix.h"

using namespace std;

struct SphereExtremes { 
  int max_x, max_y, min_x, min_y;
  SphereExtremes(int lx=0, int ly=0, int sx=0, int sy=0) : max_x(lx), max_y(ly), min_x(sx), min_y(sy){ 
  }
};

struct pixel { 
  int x, y, brightness;
  pixel(int i=0, int j=0, int b=0) : x(i), y(j), brightness(b){}
};

class Sphere{

public:

  Sphere (Image* si, const char* params_fname) { 
    setParamsFromFile(params_fname);
    img = si;
  }

  Sphere (Image* si, pair<float, float> c, float r) : center(c), radius(r){
    img = si;
  };

  Sphere (Image* labeled_img, pair<float, float> c, int label=1) : center(c) { 
    radius = calcRadius(labeled_img, label);
  };

  pair <float, float> getCenter() { return center; };

  float getRadius() { return radius; };

  Matrix findLightSource(){
    pixel b = findBrightestPixel();
    Matrix normal = findNormal(b.x, b.y);
    float magnitude = magnitude(normal);
    return normal * (b.brightness / magnitude);
  }

private:
  pair <float, float> center;
  float radius;
  Image* img;

  void setParamsFromFile(const char* params_fname);

  float calcRadius(Image* labeled_img, int label);

  SphereExtremes calcSphereExtremeties(Image* labeled_img, int label);

  Matrix findNormal(int i, int j);

  pixel findBrightestPixel();
};

#endif