#ifndef OBJECT_LABELER_H
#define OBJECT_LABELER_H

#include <iostream>
#include <vector>
#include <set>

#include "../pgm/Image.h"

using namespace std;

class ObjectLabeler{

public:
  ObjectLabeler(){
    // initialize equivalencies with empty set so labels start at 1 not 0
    set<int> empty_set;
    equivalencies.push_back(empty_set);
    label_count = 0;
  }

  void labelObjects(Image* binary_img, Image* labeled_img){
    // First pass
    ScanAndLabel(binary_img, labeled_img);

    // Second pass
    ResolveEquivalences(labeled_img);

    // Set number of objects for labeled_img
    labeled_img->setColors(getNumObjects());
  }

  int getNumObjects() {return calcNumObjects();}

private:
  vector < set<int> > equivalencies;
  int label_count;

  int calcNumObjects();

  void ScanAndLabel(Image* binary_img, Image* labeled_img);

  void ResolveEquivalences(Image* labeled_img);

  void AddToEquivalencyTable(int labelA, int labelB);

  int getEquivalentLabel(int label);

  int hasEquivalentLabel(int label);
};

#endif