#include "Sphere.h"

int Sphere::calcRadius(Image* labeled_img, int label){ 
 
  SphereExtremes se = calcSphereExtremeties(labeled_img, label);

  int r;

  return r;
}

SphereExtremes Sphere::calcSphereExtremeties(Image* labeled_img, int label){
  int minX=0, minY=0, maxX=0, maxY=0;
  bool minXfound = false, minYfound = false;

  // Scan each pixel
  int rows = labeled_img->getNRows();
  int cols = labeled_img->getNCols();
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){

      // look only at correctly labeled pixels
      if (labeled_img->getPixel(i,j) == label){

        // set minX and minY to coords of first labeled pixel
        if (!minXfound){ 
          minXfound = true;
          minX = i;
        }
        if (!minYfound){ 
          minYfound = true;
          minY = j;
        }

        // update minY if labels are found in lower cols
        if (minY > j){ minY = j; }

        // update maxs as labels are found in higher rows or cols
        if (maxX < i){ maxX = i; }
        if (maxY < j){ maxY = j; }

      }
    } 
  }

  // Create new SphereExtremes struct and return
  SphereExtremes se(maxX, maxY, minX, minY);
  return se;
}
