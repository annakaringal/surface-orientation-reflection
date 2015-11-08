#include "Sphere.h"

int Sphere::calcRadius(Image* labeled_img, int label){ 
 
  SphereExtremes se = calcSphereExtremeties(labeled_img, label);

  int r;

  return r;
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
