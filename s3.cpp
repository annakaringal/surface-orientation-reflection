#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Validation.h"
#include "pgm/Image.h"
#include "Sphere.h"

using namespace std;

int SPHERE_ARGS[] = {2,3,4};

int main(int argc, const char * argv[]) {
    if (argc != 8) {
      cerr << "ERROR: Invalid number of arguments." << endl;
      exit(-1);
    }

    const char* input_dirs_fname = argv[1];
    const char* output_img_fname = argv[7];
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


    return 0;
}
