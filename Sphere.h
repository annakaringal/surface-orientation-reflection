#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "pgm/Image.h"
#include "Validation.h"

using namespace std;

struct SphereExtremes { 
  int max_x;
  int max_y;
  int min_x; 
  int min_y;

  SphereExtremes(int lx=0, int ly=0, int sx=0, int sy=0) : max_x(lx), max_y(ly), min_x(sx), min_y(sy){ 
  }
};

class Sphere{

public:

  Sphere (Image* si, const char* params_fname) : image(si) { 
    setParamsFromFile(params_fname);
  }

  Sphere (Image* si, pair<float, float> c, int r) : image(si), center(c), radius(r){};

  Sphere (Image* labeled_img, pair<float, float> c, int label=1) : center(c) { 
    radius = calcRadius(labeled_img, label);
  };

  pair <float, float> getCenter() { return center; };

  int getRadius() { return radius; };

private:
  pair <float, float> center;
  int radius; 
  Image* img;

  void setParamsFromFile(const char* params_fname);

  int calcRadius(Image* labeled_img, int label);

  SphereExtremes calcSphereExtremeties(Image* labeled_img, int label);

};

#endif