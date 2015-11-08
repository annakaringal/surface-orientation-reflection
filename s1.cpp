#include <iostream>
#include <cstdlib>

#include "BinaryImage.h"
#include "Validation.h"
#include "pgm/Image.h"
#include "objects/Object.h"
#include "objects/ObjectLabeler.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 3) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }

    const char* input_img_fname = argv[1];
    const char* output_img_fname = argv[3];

    // Check if threshold is valid int and set to variable
    if (!isValidType<int, const char*>(argv[2])){
      cerr << "ERROR: Invalid threshold number." << endl;
      exit(-1);
    }
    int threshold = atoi(argv[2]);

    // Read image from input file 
    Image* input_img = new Image;
    if (readImage(input_img, input_img_fname) < 0) {
      cerr << "ERROR: Something went wrong reading the input image" << endl;
      exit(-1);
    }

    // Convert to binary
    Image* binary_img = new Image;
    convertToBinary(input_img, binary_img, threshold);

    // Label objects in image
    ObjectLabeler labeler;
    Image* labeled_img = new Image;
    labeler.labelObjects(binary_img, labeled_img);

    pair <float, float> center = 

    delete input_img;
    delete binary_img;
    delete labeled_img;

    return 0;
}
