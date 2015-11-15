/*****************************************************************************
 Title:             s2.cpp
 Author:            Anna Cristina Karingal
 Created on:        November 8, 2015
 Description:       Given the sphere center and radius, estimates the direction
                    vector of the light source of the sphere for each image by
                    finding the normal of the sphere at the brightest pixel.
                    Writes the vector for the lightt source of each image
                    as a three numbers on a line in the output file.

 Requirements:      - all sphere images contain the same sphere at the same
                        position in the image
                    - the spheres in the image have the same center and radius as
                        given by the input parameters file
 Build:             Compile by running 'make s2' in the working directory
 
 Usage:             ./s2 input_params_file.txt sphere_img_1.pgm sphere_img_2.pgm sphere_img_3.pgm  output_directions_file.txt
 
 Last Modified:     November 13, 2015  
 *****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "pgm/Image.h"
#include "Validation.h"
#include "Sphere.h"

using namespace std;

int SPHERE_ARGS[] = {2,3,4};

int main(int argc, const char * argv[]) {
    if (argc != 6) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }
    const char* input_params_fname = argv[1];
    const char* output_fname = argv[5];
    vector<const char*> sphere_fnames; 
    for (int i=0; i < argc - 3; i++){
        sphere_fnames.push_back(argv[SPHERE_ARGS[i]]);
    }

    // Create new sphere images from files, add to vector
    vector<Image*> sphere_images;
    for(int i=0; i < sphere_fnames.size(); i++){
        Image* img = new Image;
        if (readImage(img, sphere_fnames[i]) < 0) {
          cerr << "ERROR: Something went wrong reading the input image" << endl;
          exit(-1);
        }
        sphere_images.push_back(img);
    }

    // Create first sphere from params file and add to vector
    Sphere* sphere_from_file = new Sphere(sphere_images[0], input_params_fname);
    vector<Sphere*> spheres;
    spheres.push_back(sphere_from_file);

    // Create remaining spheres, add to vector
    for(int i=1; i < sphere_images.size(); i++){
        Sphere* s = new Sphere(sphere_images[i], sphere_from_file->getCenter(), sphere_from_file->getRadius());
        spheres.push_back(s);
    }

    // Open output file
    ofstream writef;
    writef.open(output_fname);
    if (writef.fail()) {
        cerr << "ERROR: Something went wrong reading the output file" << endl;
      exit(-1);
    }

    // Write brightness vector of each sphere to file
    if (writef.is_open()) {
        for(int i=0; i < spheres.size(); i++){
            Matrix ls = spheres[i]->findLightSource();
            writef << ls.getValue(0,0) << " ";
            writef << ls.getValue(0,1) << " ";
            writef << ls.getValue(0,2) << endl;
        }
    }
    writef.close();

    // Clean up and return
    for (int i=0; i < spheres.size(); i++){
        delete spheres[i];
        delete sphere_images[i];
    }
    return 0;
}
