#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "pgm/Image.h"
#include "Validation.h"

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

vector<int> scaleVectorToLength(vector<int> vec, int length);

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

  vector<int> findLightSource(){
    pixel b = findBrightestPixel();
    vector<int> normal = findNormal(b.x, b.y);
    return scaleVectorToLength(normal, b.brightness);
  }

private:
  pair <float, float> center;
  float radius; 
  Image* img;

  void setParamsFromFile(const char* params_fname);

  float calcRadius(Image* labeled_img, int label);

  SphereExtremes calcSphereExtremeties(Image* labeled_img, int label);

  vector<int> findNormal(int i, int j);

  pixel findBrightestPixel();
};

#endif