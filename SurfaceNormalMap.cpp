#include "SurfaceNormalMap.h"

void drawBorder(Image* img, int r, int c, int color){ 
  img->setPixel(r-1,c,color);
  img->setPixel(r,c-1,color);
  img->setPixel(r,c+1,color);
  img->setPixel(r+1,c,color);
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
  vector <Matrix> raw_ls;
  if (readf.is_open()){
      // For each line in file
      while(getline(readf, params)){
        // Split up line into different vars & save as new matrix
        istringstream pss(params);
        Matrix ls(1,3);
        for(int i=0; i<3; i++){
            string p;    
            getline(pss, p,' ');
            if (!isValidType<int, string>(p)){
              cerr << "ERROR: Light source vector  must be an integer." << endl;
              exit(-1);
            }
            float p_int = atof(p.c_str());
            if (i==0){
                ls.setValue(0,i,p_int);
            } else if (i == 1){
                ls.setValue(0,i,p_int);
            } else {
                ls.setValue(0,i,p_int);
            }
        }
        raw_ls.push_back(ls);
      }
  }
  readf.close();

  // Make light sources matrix the correct size
  light_sources = new Matrix(raw_ls.size(), 3);

  // Find average of magnitudes of light sources.
  float avg_mag = 0;
  for (int i=0; i<raw_ls.size(); i++){
    avg_mag += magnitude(raw_ls[i]);
  }
  avg_mag = avg_mag / float(raw_ls.size());

  // Scale raw light source and save scaled values to light_sources
  for (int i=0; i<raw_ls.size(); i++){
    Matrix scaled = raw_ls[i] * (avg_mag / magnitude(raw_ls[i]));
    light_sources->setValue(i, 0, scaled.getValue(0,0));
    light_sources->setValue(i, 1, scaled.getValue(0,1));
    light_sources->setValue(i, 2, scaled.getValue(0,2));
  }

  // Set light sources inverse as well
  light_sources_inverse = light_sources->inverse();
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

Matrix SurfaceNormalMap::calcAlbedoNormal(int r, int c){
  // Get brightness intensities for each of the 3 images in images
  Matrix intensities(3,1);
  intensities.setValue(0,0,float(images[0]->getPixel(r,c)));
  intensities.setValue(1,0,float(images[1]->getPixel(r,c)));
  intensities.setValue(2,0,float(images[2]->getPixel(r,c)));

  // Multiply light_source_inverse by intensities to get albedo * normal
  return light_sources_inverse * intensities;
}

Matrix SurfaceNormalMap::calcNormal(int r, int c){
  // Get the albedo & normal as a single matrix
  Matrix albedo_normal = calcAlbedoNormal(r,c);

  // Albedo is the magnitude, so divide by magnitude to get normal vector
  float mag = magnitude(albedo_normal);
  Matrix normal(3,1);
  normal.setValue(0,0, albedo_normal.getValue(0,0) / mag),
  normal.setValue(1,0, albedo_normal.getValue(1,0) / mag);
  normal.setValue(2,0, albedo_normal.getValue(2,0) / mag);
  return normal;
}

float SurfaceNormalMap::calcAlbedo(int r, int c){
  // Get the albedo & normal as a single matrix
  // Albedo is the magnitude of this matrix
  Matrix albedo_normal = calcAlbedoNormal(r,c);
  return magnitude(albedo_normal);
}

void SurfaceNormalMap::drawNormal(int r, int c, Matrix normal, Image* img){
  Matrix scaled = normal * (10 / magnitude(normal));
  int normal_end_x = r + scaled.getValue(0,0);
  int normal_end_y = c + scaled.getValue(1,0);
  line(img, r, c, normal_end_x, normal_end_y, 255); 
}

void SurfaceNormalMap::generateAlbedoMap(int threshold){
  int rows = images[0]->getNRows();
  int cols = images[0]->getNCols();
  max_albedo = -INFINITY;

  for (int i=0; i<rows; i++){
    vector<float> row; 
    for (int j=0; j<cols; j++){
      if (visibleInAllImages(i,j,threshold)){
        float a = calcAlbedo(i,j);
        row.push_back(a);
        if (a > max_albedo){
          max_albedo = a;
        } 
      } else { 
        row.push_back(0);
      }
    }
    albedo_map.push_back(row);
  }
}

void SurfaceNormalMap::shadeAlbedo(Image* output_img){
  float scale_factor = 255 / max_albedo;

  for (int i=0; i<output_img->getNRows(); i++){
    for (int j=0; j<output_img->getNCols(); j++){
      if (albedo_map[i][j] != 0 ){
        output_img->setPixel(i,j, albedo_map[i][j] * scale_factor);
      }
    }
  }
}