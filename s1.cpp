/*****************************************************************************
 Title:             s1.cpp
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Calculates the center and radius of a sphere object in a
                    single image, assuming orthographic projection.
 Build:             Compile by running 'make s1' in the working directory
 
 Usage:             ./s1 input_img.pgm input_threshold_value output_params_file.txt
 
 Last Modified:     November 8, 2015  
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "BinaryImage.h"
#include "Validation.h"
#include "pgm/Image.h"
#include "objects/Object.h"
#include "objects/ObjectLabeler.h"
#include "objects/ImageObjectDatabase.h"
#include "Sphere.h"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 4) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }

    const char* input_img_fname = argv[1];
    const char* output_fname = argv[3];

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

    // Label objects in image and store in image database
    ObjectLabeler labeler;
    Image* labeled_img = new Image;
    labeler.labelObjects(binary_img, labeled_img);
    ImageObjectDatabase iodb(labeled_img);

    // create new sphere with labeled image and center
    pair <float, float> center = iodb.getObject(1)->calculateCenter();
    Sphere s(labeled_img, center);

    // Open output file
    ofstream writef;
    writef.open(output_fname);
    if (writef.fail()) {
        cerr << "ERROR: Something went wrong reading the output file" << endl;
      exit(-1);
    }

    // Write sphere attributes to file
    if (writef.is_open()) {
        writef << center.first << " ";
        writef << center.second<< " ";
        writef << s.getRadius() << "\n";
    }
    writef.close();

    delete input_img;
    delete binary_img;
    delete labeled_img;

    return 0;
}
