#include "Sphere.h"

void Sphere::setParamsFromFile(const char* params_fname){
  // Open file
  ifstream readf; 
  readf.open(params_fname);
  if (readf.fail()) {
      cerr << "ERROR: Something went wrong reading the parameters file." << endl;
      exit(-1);
  }

  // Get params line from file
  string params;
  vector<string> param_strings; 
  if (readf.is_open()){
      getline(readf, params);
  }
  readf.close();

  // Parse params line and set center & radius
  istringstream pss(params);
  for(int i=0; i<3; i++){
      string p;    
      getline(pss, p,' ');

      if (!isValidType<int, string>(p)){
        cerr << "ERROR: Parameter must be an integer." << endl;
        exit(-1);
      }
      int p_int = atoi(p.c_str());

      if (i==0){
          center.first = p_int;
      } else if (i == 1){
          center.second = p_int;
      } else {
          radius = p_int;
      }
  }
}

float Sphere::calcRadius(Image* labeled_img, int label){ 
 
  // calculate max & min rows & cols
  SphereExtremes se = calcSphereExtremeties(labeled_img, label);

  // calculate horizontal & vertical radii & return avg
  int vert_rad = (se.max_x - se.min_x) / 2; 
  int hor_rad = (se.max_y - se.min_y) / 2; 
  return (vert_rad + hor_rad) / 2;
}

SphereExtremes Sphere::calcSphereExtremeties(Image* labeled_img, int label){
  int min_x=0, min_y=0, max_x=0, max_y=0;
  bool min_x_found = false, min_y_found = false;

  // Scan each pixel
  int rows = labeled_img->getNRows();
  int cols = labeled_img->getNCols();
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){

      // look only at correctly labeled pixels
      if (labeled_img->getPixel(i,j) == label){

        // set min_x and min_y to coords of first labeled pixel
        if (!min_x_found){ 
          min_x_found = true;
          min_x = i;
        }
        if (!min_y_found){ 
          min_y_found = true;
          min_y = j;
        }

        // update min_y if labels are found in lower cols
        if (min_y > j){ min_y = j; }

        // update maxs as labels are found in higher rows or cols
        if (max_x < i){ max_x = i; }
        if (max_y < j){ max_y = j; }

      }
    } 
  }

  // Create new SphereExtremes struct and return
  SphereExtremes se(max_x, max_y, min_x, min_y);
  return se;
}

pixel Sphere::findBrightestPixel(){
  int max_val = 0, max_i = 0, max_j = 0;
  int rows = img->getNRows();
  int cols = img->getNCols();

  // Scan all pixels
  // Update vars if pixel is brighter than max_val
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){
      int cur = img->getPixel(i,j);
      if (cur > max_val){
        max_val = cur;
        max_i = i; 
        max_j = j;
      }
    }
  }
  pixel brightest(max_i, max_j, max_val);
  return brightest;
}

Matrix* Sphere::findNormal(int i, int j){
  // Calculate x-x0 and y-y0
  int dx = i-center.first;
  int dy = j-center.second;

  // Calculate z - z0 
  int dz = sqrt(abs((dx * dx) + (dy * dy) - int(radius*radius)));

  // Vector is x-x0, y-y0, z-z0
  Matrix* normal = new Matrix(1,3);
  normal->setValue(0,0,dx); 
  normal->setValue(0,1,dy); 
  normal->setValue(0,2,dz); 
  return normal;
}
