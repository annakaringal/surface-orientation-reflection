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

    SurfaceNormalMap snm(input_dirs_fname);

    return 0;
}
