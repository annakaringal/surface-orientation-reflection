#ifndef SURFACE_NORMAL_MAP_H
#define SURFACE_NORMAL_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "pgm/Image.h"
#include "Validation.h"
#include "Matrix.h"

using namespace std;

void drawBorder(Image* img, int r, int c, int color);

class SurfaceNormalMap{

public:
  SurfaceNormalMap(const char* dirs_fname, vector<Image*> obj_imgs, int step, int threshold) : images(obj_imgs) {
    light_sources = new Matrix(3,3);
    setLightSourcesFromFile(dirs_fname);
    generateGridPoints(step, threshold);
  };

  void drawMap(Image* output_img){
    drawGridPoints(output_img);
    calcAndDrawNormals(output_img);
  }

private:
  Matrix* light_sources;
  vector< pair<int, int> > grid_points;
  vector<Image*> images;

  void setLightSourcesFromFile(const char* fname);

  void generateGridPoints(int step, int threshold);

  bool visibleInAllImages(int r, int c, int threshold);

  void drawGridPoints(Image* output_img);

  void calcAndDrawNormals(Image* output_img);

  Matrix calcNormal(int r, int c);

  void drawNormal(int r, int c, Matrix normal, Image* img);

};

#endif

