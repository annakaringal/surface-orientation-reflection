#include "3dVec.h"

3dVec 3dVec::calcMagnitude(){
  float mag_sq = getX()*getX() + getY()*getY() + getZ()*getZ();
  return sqrt(mag_sq);
}

void 3dVec::scaleVecLength(3dVec vec, int length) { 
  // Calculate magnitude to get scale factor
  float scale_factor = float(length) / magnitude();

  setX(float(getX()) * scale_factor);
  setY(float(getY()) * scale_factor);
  setZ(float(getZ()) * scale_factor);
}

vector <3dVec> invert(vector<3dVec> 3x3_vec){

}

int matrixProduct(int r, vector<3dVec> 3x3_vec, 3dVec 3x1_vec){
  int prod = 3x3_vec[r].getX() * 3x1_vec.getX();
  prod += 3x3_vec[r].getY() * 3x1_vec.getY();
  prod += 3x3_vec[r].getZ() * 3x1_vec.getZ();
  return prod;
}