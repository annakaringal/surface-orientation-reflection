/*****************************************************************************
 Title:             s3.cpp
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Uses photometric stereo technigues to estimate the surface
                    normal of the object using three different images of the same
                    object under three different known light sources. Draws these
                    normals as lines on the first image of the object.
 Requirements:      - The light source vectors in the input text file are the same
                      as those for the given images, in the same order.
                    - Threshold is an integer >= 0 && <= 255.
                    - Step is an integer >=0 and <= the number of rows or columns 
                    in the image, whichever is smaller.
 Build:             Compile by running 'make s3' in the working directory
 
 Usage:             ./s3 light_sources_vectors.txt object1.img object2.img object3.img step threshold output_img.pgm
 
 Last Modified:     November 14, 2015  
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Validation.h"
#include "pgm/Image.h"
#include "SurfaceNormalMap.h"

using namespace std;

int OBJ_ARGS[] = {2,3,4};

int main(int argc, const char * argv[]) {
    if (argc != 8) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }

    const char* input_dirs_fname = argv[1];
    const char* output_img_fname = argv[7];
    vector<const char*> obj_fnames; 
    for (int i=0; i < sizeof(OBJ_ARGS) / sizeof(int); i++){
        obj_fnames.push_back(argv[OBJ_ARGS[i]]);
    }

    // Create new sphere images from files, add to vector
    vector<Image*> obj_images;
    for(int i=0; i < obj_fnames.size(); i++){
        Image* img = new Image;
        if (readImage(img, obj_fnames[i]) < 0) {
          cerr << "ERROR: Something went wrong reading the input image" << endl;
          exit(-1);
        }
        obj_images.push_back(img);
    }

    // Check if step & threshold are valid ints and set to variables
    if (!isValidType<int, const char*>(argv[6])){
      cerr << "ERROR: Invalid threshold number." << endl;
      exit(-1);
    }
    int threshold = atoi(argv[6]);

    if (!isValidType<int, const char*>(argv[5])){
      cerr << "ERROR: Invalid step number." << endl;
      exit(-1);
    }
    int step = atoi(argv[5]);

    // Read input directions file and store in surface normal map
    SurfaceNormalMap snm(input_dirs_fname, obj_images, step, threshold);

    // Create copy of first image and draw normals map
    Image* output_img = new Image(*obj_images[0]);

    snm.drawNormalMap(output_img);

    // Write output image to file
    if (writeImage(output_img, output_img_fname) < 0){
      cerr << "ERROR: Something went wrong writing the output image" << endl;
      exit(-1);
    }


    // Clean up and return
    for (int i=0; i < obj_images.size(); i++){
        delete obj_images[i];
    }

    return 0;
}
