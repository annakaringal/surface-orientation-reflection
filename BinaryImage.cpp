#include "BinaryImage.h"

int convertToBinary(Image* greyscale_img, Image* binary_img, int threshold){
  // Check if threshold is valid
  if (threshold > greyscale_img->getColors() || threshold < 0) { return -1; }

  // Set rows & cols of binary_img
  int rows = greyscale_img->getNRows();
  int cols = greyscale_img->getNCols();
  binary_img->setSize(rows, cols);
  binary_img->setColors(1);

  // Set colors of binary_img based on given threshold
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){
      if (greyscale_img->getPixel(i, j) < threshold){
        if (binary_img->setPixel(i, j, 0) < 0) {
          return -1;
        };
      } else {
        if (binary_img->setPixel(i, j, 1) < 0){
          return -1;
        }
      }
    }
  }

  return 0;
}
