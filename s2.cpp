#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "pgm/Image.h"
#include "Validation.h"
#include "Sphere.h"

using namespace std;

int SPHERE_ARGS[] = {2,3,4};
int NUM_SPHERES = 3;

int main(int argc, const char * argv[]) {
    if (argc != 6) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }
    const char* input_params_fname = argv[1];
    const char* output_fname = argv[5];
    vector<const char*> sphere_fnames; 
    for (int i=0; i < NUM_SPHERES; i++){
        sphere_fnames.push_back(argv[SPHERE_ARGS[i]]);
    }

    // Create new sphere images from files, add to vector
    vector<Image*> sphere_images;
    for(int i=0; i < NUM_SPHERES; i++){
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
    for(int i=1; i < NUM_SPHERES; i++){
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
        for(int i=0; i < NUM_SPHERES; i++){
            vector<int> ls = spheres[i]->findLightSource();
            writef << ls[0] << " ";
            writef << ls[1] << " ";
            writef << ls[2] << endl;
        }
    }
    writef.close();

    // Clean up and return
    for (int i=0; i < NUM_SPHERES; i++){
        delete spheres[i];
        delete sphere_images[i];
    }
    return 0;
}
