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
  int x, y, z;
  lightsource(int i=0, int j=0, int k=0) : x(i), y(j), z(k){}
};

class SurfaceNormalMap{

public:
  SurfaceNormalMap(const char* dirs_fname, vector<Image*> obj_imgs, int step, int threshold) : images(obj_imgs) {
    setLightSourcesFromFile(dirs_fname);
    generateGridPoints(step, threshold);
  };

  void drawMap(Image* output_img){
    drawGridPoints(output_img);
    calculateNormals();
    drawNormals(output_img);
  }

private:
  vector<lightsource> light_sources;
  vector< pair<int, int> > grid_points;
  vector<Image*> images;

  void setLightSourcesFromFile(const char* fname);

  void generateGridPoints(int step, int threshold);

  bool visibleInAllImages(int r, int c, int threshold);

  void drawGridPoints(Image* output_img);

  void calculateNormals();

  void drawNormals(Image* output_img);
};

#endif

