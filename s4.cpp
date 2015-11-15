/*****************************************************************************
 Title:             s4.cpp
 Author:            Anna Cristina Karingal
 Created on:        November 14, 2015
 Description:       Uses photometric stereo technigues to estimate the albedo of
                    the object using three different images of the same
                    object under three different known light sources. Shades the
                    albedo onto a copy of the image. 
 Requirements:      - The light source vectors in the input text file are the same
                      as those for the given images, in the same order.
                    - Threshold is an integer >= 0 && <= 255.
 Build:             Compile by running 'make s4' in the working directory
 
 Usage:             ./s4 light_sources_vectors.txt object1.img object2.img object3.img threshold output_img.pgm
 
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
    if (argc != 7) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }

    const char* input_dirs_fname = argv[1];
    const char* output_img_fname = argv[6];
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
    if (!isValidType<int, const char*>(argv[5])){
      cerr << "ERROR: Invalid threshold number." << endl;
      exit(-1);
    }
    int threshold = atoi(argv[5]);

    // Read input directions file and store in surface normal map
    SurfaceNormalMap snm(input_dirs_fname, obj_images, threshold);

    // Create copy of first image and shade with albedo
    Image* output_img = new Image(*obj_images[0]);

    snm.shadeWithAlbedo(output_img);

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
