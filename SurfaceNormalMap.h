#ifndef SURFACE_NORMAL_MAP_H
#define SURFACE_NORMAL_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "pgm/Image.h"
#include "Validation.h"
#include "Matrix.h"

using namespace std;

void drawBorder(Image* img, int r, int c, int color);

class SurfaceNormalMap{

public:
  SurfaceNormalMap(const char* dirs_fname, vector<Image*> obj_imgs, int step, int threshold) : images(obj_imgs) {
    setLightSourcesFromFile(dirs_fname);
    generateGridPoints(step, threshold);
  };


  SurfaceNormalMap(const char* dirs_fname, vector<Image*> obj_imgs, int threshold) : images(obj_imgs) {
    setLightSourcesFromFile(dirs_fname);
    generateAlbedoMap(threshold);
  };

  ~SurfaceNormalMap(){
    delete light_sources;
  }

  void drawNormalMap(Image* output_img){
    drawGridPoints(output_img);
    calcAndDrawNormals(output_img);
  }

  void shadeWithAlbedo(Image* output_img){
    shadeAlbedo(output_img);
  }

private:
  Matrix* light_sources;
  Matrix light_sources_inverse;
  vector< pair<int, int> > grid_points;
  vector<Image*> images;
  vector< vector<float> > albedo_map;
  float max_albedo;

  void setLightSourcesFromFile(const char* fname);

  void generateGridPoints(int step, int threshold);

  bool visibleInAllImages(int r, int c, int threshold);

  void drawGridPoints(Image* output_img);

  void calcAndDrawNormals(Image* output_img);

  Matrix calcAlbedoNormal(int r, int c);

  Matrix calcNormal(int r, int c);

  void drawNormal(int r, int c, Matrix normal, Image* img);

  float calcAlbedo(int r, int c);

  void generateAlbedoMap(int threshold);

  void shadeAlbedo(Image* output_img);
};

#endif

