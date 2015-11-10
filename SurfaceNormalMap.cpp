#include "SurfaceNormalMap.h"

void drawBorder(Image* img, int r, int c, int color){ 
  img->setPixel(r-1,c-1,color);
  img->setPixel(r-1,c,color);
  img->setPixel(r-1,c+1,color);
  img->setPixel(r,c-1,color);
  img->setPixel(r,c+1,color);
  img->setPixel(r+1,c-1,color);
  img->setPixel(r+1,c,color);
  img->setPixel(r+1,c+1,color);
}

void SurfaceNormalMap::setLightSourcesFromFile(const char* fname){
  // Open file
  ifstream readf; 
  readf.open(fname);
  if (readf.fail()) {
      cerr << "ERROR: Something went wrong reading the parameters file." << endl;
      exit(-1);
  }

  // Get params line from file
  string params;
  vector<string> param_strings; 
  if (readf.is_open()){

      // For each line in file
      while(getline(readf, params)){
        // Split up line into different vars & save as new lightsource  to vector
        3dVec ls;
        istringstream pss(params);
        for(int i=0; i<3; i++){
            string p;    
            getline(pss, p,' ');

            if (!isValidType<int, string>(p)){
              cerr << "ERROR: Light source vector  must be an integer." << endl;
              exit(-1);
            }
            int p_int = atoi(p.c_str());

            if (i==0){
                ls.setX(p_int);
            } else if (i == 1){
                ls.setY(p_int);
            } else {
                ls.setZ(p_int);
            }
        }
        light_sources.push_back(ls);
      }
  }
  readf.close();

};

void SurfaceNormalMap::generateGridPoints(int step, int threshold){

  int rows = images[0]->getNRows();
  int cols = images[0]->getNCols();

  for (int i=0; i<rows; i += step){
    for (int j=0; j<cols; j += step){
      if (visibleInAllImages(i,j,threshold)){
        grid_points.push_back(make_pair(i,j));
      }
    }
  }

};

bool SurfaceNormalMap::visibleInAllImages(int r, int c, int threshold){
  bool visible = true;

  for(int i=0;i<images.size();i++){
    if (images[i]->getPixel(r,c) < threshold){
      visible = false; 
      break;
    }
  }

  return visible;
};

void SurfaceNormalMap::drawGridPoints(Image* output_img){
  int color=0;

  // For each stored gridpoint
  for (int i=0; i<grid_points.size(); i++){

    // Color point black
    int r = grid_points[i].first;
    int c = grid_points[i].second;
    output_img->setPixel(r,c,color);

    // Draw 1px border around point for visibility
    drawBorder(output_img, r, c, color);
  }
};

void SurfaceNormalMap::calcAndDrawNormals(){
  for (int i=0; i<grid_points.size(); i++){
    3dvec n = calcNormal(grid_points[i].first, grid_points[i].second);
    drawNormal(n, output_img);
  }
}

3dVec SurfaceNormalMap::calcNormal(int r, int c){
  // Get brightness for each of the 3 images in images
  3dVec intensities(images[0]->getPixel(r,c), 
                    images[1]->getPixel(r,c), 
                    images[2]->getPixel(r,c));

  // Find inverse of normals to light sources
  vector <3dVec> light_sources_inverse = invert(light_sources);

  // Multiply lighht_source_inverse by intensities
  3dVec N(matrixProduct(0, 0, light_sources_inverse, N),
          matrixProduct(0, 1, light_sources_inverse, N),
          matrixProduct(0, 2, light_sources_inverse, N));

  // divide by magnitude to get orientation of normal
  float magnitude = N.magnitude();
  3dVec normal(N.get(X) / magnitude,
               N.get(Y) / magnitude,
               N.get(Z) / magnitude);
  return normal;
}