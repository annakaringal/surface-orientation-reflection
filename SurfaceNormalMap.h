#ifndef SURFACE_NORMAL_MAP_H
#define SURFACE_NORMAL_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "pgm/Image.h"
#include "Validation.h"

using namespace std;

struct lightsource { 
  int x; 
  int y; 
  int z;

  lightsource(int i=0, int j=0, int k=0) : x(i), y(j), z(k){}
};

class SurfaceNormalMap{

public:

private:

};

#endif

