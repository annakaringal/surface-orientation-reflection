#ifndef IMAGE_OBJECT_DB_H
#define IMAGE_OBJECT_DB_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdlib>

#include "../pgm/Image.h"
#include "Object.h"
#include "../Validation.h"

#define AREA_TOLERANCE_PERCENTAGE 0.15
#define ROUNDNESS_TOLERANCE_PERCENTAGE 0.15

using namespace std;

class ImageObjectDatabase{

public:
  // Create image object database from image
  ImageObjectDatabase(Image* labeled_img) : img (labeled_img) {
    num_objects = labeled_img->getColors();
    generateObjects();
  };

  // Create empty image object db
  ImageObjectDatabase() { 
    num_objects = 0;
  };

  // Make sure all objects are deallocated
  ~ImageObjectDatabase(){
    for (int i=0; i<objects.size(); i++){
      delete objects[i];
    }
  }

  // Returns number of objects in database
  int getNumObjects() const { return num_objects; };

  // Write database to file
  int writeDatabase(const char* fname);

  // Returns pointer to object with label
  Object* getObject(int label) const { return objects[label-1]; };

  // Returns label of object match if obj has a close match within the database
  int hasMatch(Object* obj);

  // Add a new object to the database
  void addObject(Object* obj);

private:
  Image* img;
  int num_objects;
  vector<Object*> objects;

  // Create new objects from img with all object attributes and properties
  // Precondition: img exists
  void generateObjects();

  // Calculate properties of all objects in image
  // Precondition: objects is a vector containing only and all objects in img
  void calculateObjectProperties();
};

// Read existing database from file and populate iodb with data
int readDatabase(ImageObjectDatabase* iodb, const char* fname);

#endif