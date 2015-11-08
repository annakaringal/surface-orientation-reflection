#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <vector>
#include <math.h>

#include "pgm/Image.h"
#include "Validation.h"

using namespace std;

struct SphereExtremes { 
  int maxX;
  int maxY;
  int minX; 
  int minY;

  SphereExtremes(int lx=0, int ly=0, int sx=0, int sy=0) : maxX(lx), maxY(ly), minX(sx), minY(sy){ 
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