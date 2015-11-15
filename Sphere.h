/*****************************************************************************
 Title:             Sphere.h
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Class to calculate the center and radius of a sphere from
                    an image (assuming orthographic projection) as well as 
                    find the normal of any pixel on the sphere and the orientation
                    of the sphere's light source using the normal of the brightest
                    pixel.
 
 Last Modified:     November 14, 2015
 *****************************************************************************/

#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <cstdlib>

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

// Sphere class that stores and calculates attributes for a sphere in a given image
//
// CONSTRUCTION: - from image and file containing center coordinates and radius
//               - from given image, center and radius params
//               - from labeled image of the sphere and the center coordinates
//
// ******************PUBLIC OPERATIONS*********************
// float, float getCenter() --> returns center of the sphere as a pair
//                              where x & y coordinates are first & second values
//                              respectively
// float getRadius()        --> returns radius of the sphere
// void findLightSource()   --> returns orientation of light source as a 1x3 matrix

class Sphere{

public:

  // CONSTRUCTORS
  Sphere (Image* si, const char* params_fname) { 
    // Set center & radius from given file
    setParamsFromFile(params_fname);
    // set pointer to image of sphere
    img = si;
  }

  Sphere (Image* si, pair<float, float> c, float r) : center(c), radius(r){
    // set pointer to image of sphere
    img = si;
  };

  // Initializes sphere, sets center and calculates radius from a labeled
  // image of the sphere
  // Preconditions:    - c contains the x & y coordinates of the sphere
  //                      in labeled image
  //                   - labeled_img contains a labeled image of the sphere 
  //                   - label is the number of the label of the sphere
  //                      in labeled_img
  Sphere (Image* labeled_img, pair<float, float> c, int label=1) : center(c) { 
    // calculate radius from given sphere center 
    radius = calcRadius(labeled_img, label);
  };

  // PUBLIC GETTERS
  pair <float, float> getCenter() { return center; };

  float getRadius() { return radius; };

  // Finds light source of sphere by calculating the normal of the brightest 
  // pixel. Scales this so that the length of the normal is equal to the 
  // value of the brightest pixel and returns as a 3x1 matrix.
  Matrix findLightSource(){
    // Find normal of brightest pixel as a matrix
    pixel b = findBrightestPixel();
    Matrix normal = findNormal(b.x, b.y);

    // scale so length of vector is equal to brightest pixel
    float mag = magnitude(normal);
    return normal * (b.brightness / mag);
  }

private:
  pair <float, float> center;
  float radius;
  Image* img;

  // Sets center & radius from values in a given file
  void setParamsFromFile(const char* params_fname);

  // calculates radius by taking the average of the vertical and
  // horizontal differences and dividng by two
  float calcRadius(Image* labeled_img, int label);

  // finds the uppermost, lowermost and leftmost/rightmost points of the sphere
  SphereExtremes calcSphereExtremeties(Image* labeled_img, int label);

  // calcualtes the normal at point i, j using the formula for a sphere
  // and assuming orthographic projection
  Matrix findNormal(int i, int j);

  // scans the sphere object for the pixel with the brightest value
  // returns the x & y coordinates and brightness of pixel
  pixel findBrightestPixel();
};

#endif