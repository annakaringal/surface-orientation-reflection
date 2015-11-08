#include "ObjectLabeler.h"

int ObjectLabeler::calcNumObjects(){
  return equivalencies.size() - 1;
}

void ObjectLabeler::ScanAndLabel(Image* binary_img, Image* labeled_img){
  // Get and set num of rows & cols
  int rows = binary_img->getNRows();
  int cols = binary_img->getNCols();
  labeled_img->setSize(rows, cols);

  // Scan each pixel
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++){
      // If pixel is the background, label as background.
      if (binary_img->getPixel(i,j) == 0) {
        labeled_img->setPixel(i,j,0);
      } else {
        // Current pixel is part of an object.
        // Look at already labeled neighboring pixels.

        // D has a label, current pixel gets D's label
        int D = labeled_img->getPixel(i-1,j-1);
        if (D > 0){
          labeled_img->setPixel(i,j,D);
        } else {
          int B = labeled_img->getPixel(i-1,j);
          int C = labeled_img->getPixel(i,j-1);

          // B, C and D are all background. New object!
          if (B == 0 && C == 0){
            label_count++;
            labeled_img->setPixel(i,j,label_count);

            AddToEquivalencyTable(label_count,label_count);

          // Only C has a label, current pixel gets C's label
          } else if (C > 0 && B == 0) {
            labeled_img->setPixel(i,j,C);

          // Only B has a label, current pixel gets B's label
          } else if (B > 0 && C == 0){ 
            labeled_img->setPixel(i,j,B);

          // B & C have same label, current pixel gets that label
          } else if (B == C && B > 0 && C > 0) {
            labeled_img->setPixel(i,j,B);

          // B and C are both labeled but label B != label C
          // B and C's labels are equivalent, mark as equivalent
          // current pixel gets B's label
          } else {
            labeled_img->setPixel(i,j,B);
            AddToEquivalencyTable(B,C);
          }
        }
      }
    }
  }
}

void ObjectLabeler::ResolveEquivalences(Image* labeled_img){
  // Scan each pixel
  for (int i=0; i < labeled_img->getNRows(); i++){
    for (int j=0; j < labeled_img->getNCols(); j++){
      // If pixel is not background and label has equivalency, 
      // set to lowest equivalency
      int cur_pix = labeled_img->getPixel(i,j);
      if (cur_pix > 0){
        int label = getEquivalentLabel(cur_pix);
        if (label > 0){
          labeled_img->setPixel(i,j, label);
        }
      }
    }
  }
}

void ObjectLabeler::AddToEquivalencyTable(int labelA, int labelB){
  int A = hasEquivalentLabel(labelA);
  int B = hasEquivalentLabel(labelB);

  // If one of the label exists, add the other label to the same set
  if (A >= 0 && B < 0){
    equivalencies[A].insert(labelB);
  } else if (B >= 0 && A < 0){
    equivalencies[B].insert(labelA);

  // Both labels aren't in table yet, add as new equivalency
  } else if (A < 0 && B < 0){
    set<int> equivalent_labels;
    equivalent_labels.insert(labelA);
    equivalent_labels.insert(labelB);
    equivalencies.push_back(equivalent_labels);
  
  // Both labels are in table: merge sets into lowest set, 
  // delete highest set
  } else if (A >= 0 && B >= 0 && A != B){
    int low = (A < B ? A : B);
    int high = (A < B ? B : A);
    equivalencies[low].insert(equivalencies[high].begin(), equivalencies[high].end());
    equivalencies.erase(equivalencies.begin() + high);

  // Both labels are already in same equivalency sset
  } else {
    // Do nothing
  }

}

int ObjectLabeler::hasEquivalentLabel(int label){
  // Return -1 if no equivalencies in table
  if (equivalencies.empty()) { return -1; }

  // Check every entry in equivalencies table
  for (int i=0; i < equivalencies.size(); i++){
    // If entry contains label, return index of entry
    if (equivalencies[i].find(label) != equivalencies[i].end()){
      return i;
    }
  }
  // Label not found
  return -1;
}

int ObjectLabeler::getEquivalentLabel(int label){
  // Return -1 if no label is not found in the equivalency table
  // Else return number of entry in equivalency table
  int equivalency = hasEquivalentLabel(label);
  if (equivalency < 0) {
    return -1;
  } else {
    return equivalency;
  }
}

