#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <math.h>

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

private:
  pair <float, float> center;
  int radius; 

  int calcRadius(Image* labeled_img, int label);

  SphereExtremes calcSphereExtremeties(Image* labeled_img, int label);

};

#endif