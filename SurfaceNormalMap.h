/*****************************************************************************
 Title:             SurfaceNormalMap.h
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Class to generate the surface normal map and albedo of 
                    an object in a given image, using photometric stereo and 
                    at least 3 images of the object under known light sources

 Last Modified:     November 14, 2015
 *****************************************************************************/
#ifndef SURFACE_NORMAL_MAP_H
#define SURFACE_NORMAL_MAP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <cstdlib>

#include "pgm/Image.h"
#include "Validation.h"
#include "Matrix.h"

using namespace std;

// Draws border around pixel
void drawBorder(Image* img, int r, int c, int color);

// Surface Normal Map class that stores and calculates normals and albedo for
// given object in image using photometric stereo
// 
// CONSTRUCTION: - from file containing light source direction vectors, a vector
//                  containing at least 3 different object images, step distance
//                  and threshold. This generates gridpoints for the image.
//               - from file containing light source direction vectors, a vector
//                  containing at least 3 different object images and threshold.
//                  This generates the albedo map for the image.
//
// ******************PUBLIC OPERATIONS*********************
// void drawNormalMap(oi)   --> draws normals to surface on oi at gridpoints
// void shadeWithAlbedo(oi) --> shades oi with the surface albedo of the object

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

  // sets all grid points step pixels apart: only takes into account pixels
  // whose value is over the threshold for all images
  void generateGridPoints(int step, int threshold);

  // returns true if pixel r,c is below threshold for all images, else false
  bool visibleInAllImages(int r, int c, int threshold);

  // draws gridpoints in black on the output image
  void drawGridPoints(Image* output_img);

  // calculates and draws surface normals of the object 
  void calcAndDrawNormals(Image* output_img);

  // calculates matrix that is the albedo * normal
  Matrix calcAlbedoNormal(int r, int c);

  // calculates normal to surface at given point
  Matrix calcNormal(int r, int c);

  // draws normal at given point
  void drawNormal(int r, int c, Matrix normal, Image* img);

  // calculates surface albedo at given point
  float calcAlbedo(int r, int c);

  // calculates albedo for each pixel in image that is under given threshold
  // for all images and stores in albedo_map. also calculates max value of albedo
  void generateAlbedoMap(int threshold);

  // shades albedo map on output image
  void shadeAlbedo(Image* output_img);
};

#endif

