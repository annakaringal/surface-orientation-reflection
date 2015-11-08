#ifndef SURFACE_NORMAL_MAP_H
#define SURFACE_NORMAL_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

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
  SurfaceNormalMap(const char* fname){
    setLightSourcesFromFile(fname);
  };

private:
  vector<lightsource> light_sources;
 
  void setLightSourcesFromFile(const char* fname);
};

#endif

