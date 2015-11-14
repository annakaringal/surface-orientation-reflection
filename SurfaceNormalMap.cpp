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
        // Split up line into different vars & save as new matrix
        istringstream pss(params);
        for(int i=0; i<3; i++){
            string p;    
            getline(pss, p,' ');

            if (!isValidType<int, string>(p)){
              cerr << "ERROR: Light source vector  must be an integer." << endl;
              exit(-1);
            }
            float p_int = atof(p.c_str());

            if (i==0){
                light_sources->setValue(i,0,p_int);
            } else if (i == 1){
                light_sources->setValue(i,1,p_int);
            } else {
                light_sources->setValue(i,2,p_int);
            }
        }
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

void SurfaceNormalMap::calcAndDrawNormals(Image* output_img){
  for (int i=0; i<grid_points.size(); i++){
    int x = grid_points[i].first;
    int y = grid_points[i].second;
    Matrix n = calcNormal(x,y);
    drawNormal(x, y, n, output_img);
  }
}

Matrix SurfaceNormalMap::calcNormal(int r, int c){
  // Get brightness for each of the 3 images in images
  Matrix intensities(1,3);
  intensities.setValue(0,0,float(images[0]->getPixel(r,c)));
  intensities.setValue(0,1,float(images[1]->getPixel(r,c)));
  intensities.setValue(0,2,float(images[2]->getPixel(r,c)));
  // Find inverse of normals to light sources
  Matrix light_sources_inverse = light_sources->inverse();

  // Multiply light_source_inverse by intensities
  Matrix N = light_sources_inverse * intensities;

  // divide by magnitude to get orientation of normal
  float magnitude = calcSingleColMatrixMagnitude(N);
  Matrix normal(1,3);
  normal.setValue(0,0, N.getValue(0,0) / magnitude),
  normal.setValue(0,1, N.getValue(0,1) / magnitude);
  normal.setValue(0,2, N.getValue(0,2) / magnitude);
  return normal;
}

void SurfaceNormalMap::drawNormal(int r, int c, Matrix normal, Image* img){
  Matrix scaled = normal * (10 / calcSingleColMatrixMagnitude(normal));
  float normal_end_x = r + scaled.getValue(0,1);
  float normal_end_y = c + scaled.getValue(0,2);
  line(img, r, c, int(normal_end_x), int(normal_end_y), 255); 
}