#ifndef BINARY_IMAGE_H
#define BINARY_IMAGE_H

#include <iostream>

#include "pgm/Image.h"

using namespace std;

// Converts greyscale_image to binary based on passed threshold argument
// Saves result to binary_imag
// Preconditions:   - greyscale_img is a greyscale pgm image file
//                  - binary_img is a pointer to an empty initailized Image
//                  - threshold is an int between 0 to the greyscale_img.getColors()
// Returns 0 if OK, else returns -1 if something went wrong
int convertToBinary(Image* greyscale_img, Image* binary_img, int threshold);

#endif