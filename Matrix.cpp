#include "Matrix.h"

float Matrix::getVal(int r, int c) const { return matrix[r][c]; }

void Matrix::setVal(int r, int c, float v){
  if (validRow(r) && validCol(c)) {
    matrix[r][c] = v;
  } 
  // TODO: raise excep if not valid row or col
}

int Matrix::getNRows() const { return matrix.size(); }

int Matrix::getNCols() const {
  return (getRows() > 0 ? matrix[0].size(): 0);
}

bool Matrix::validRow(int r){ return r >= 0 && r < getRows(); }

bool Matrix::validCol(int c){ return c >= 0 && c < getCols(); }

float Matrix::calcDeterminant(){
  // TODO: Raise exception if not a square matrix
  float det = 0;
  int rows = getRows();
  int cols = getCols();

  // Base case: 1x1 and 2x2 matrix
   if (rows == 1 && cols == 1){
    return getValue(0,0);
  } else if (rows == 2 && cols == 2){ 
    float a,b,c,d; 
    a = getValue(0,0);
    b = getValue(0,1);
    c = getValue(1,0);
    d = getValue(1,1);

    return a*d - b*c;
  } else {
    for (int c=0; c<cols; c++){
      if (c % 2 == 0 ){
        det += getValue(0,c) * getMinor(0,c);
      } else { 
        det -= getValue(0,c) * getMinor(0,c);
      }
    }
    return det; 
  }
}

Matrix Matrix::calcInverse(){
  // TODO: raise exception if det == 0 or is not a square matrix
  // transpose cofactor to get adjugate
  Matrix adjugate = cofactor().transpose();
  // Inverse is adjugate * 1/determinant
  return adjugate * (1/determinant());
}

Matrix Matrix::calcCofactor(){ 
  // TODO: raise exception if not square matrix
  // Cofactor is matrix of minors checkerboarded
  return minors().checkerboard();
}

Matrix Matrix::calcMinors(){ 
  // TODO: raise exception if not square matrix
  Matrix m(getRows(), getCols());
   for (int i=0; i<getRows(); i++){
      for (int j=0; j<getCols(); j++){
        m.setValue(i,j, getMinor(i,j));
      }
   }
   return m;
}

float Matrix::getMinor(int r, int c){
  // TODO: raise exception if not square matrix
  Matrix minor(getRows()-1, getCols()-1);
  for (int i=0; i<getRows(); i++){
    for (int j=0; j<getCols(); j++){
      if (i!=r && j!=c){
        if (i<r && j<c){
          minor.setValue(i,j, getValue(i,j));
        } else if (i<r && j>c){
          minor.setValue(i,j-1, getValue(i,j));
        } else if (i>r && j<c){
          minor.setValue(i-1,j, getValue(i,j));
        } else {
          minor.setValue(i-1,j-1, getValue(i,j));
        }

      }
    } 
  }
  return minor.determinant();
}

Matrix Matrix::operator* (float x){
  Matrix new_m(getRows(), getCols());
   for (int i=0; i<getRows(); i++){
      for (int j=0; j<getCols(); j++){
        new_m.setValue(i,j, getValue(i,j) * x);
      }
   }
  return new_m;
}

Matrix Matrix::calcTranspose(){ 
  Matrix transpose(getCols(), getRows());
   for (int i=0; i<getRows(); i++){
      for (int j=0; j<getCols(); j++){
        transpose.setValue(j,i, getValue(i,j));
      }
   }
  return transpose;
}

Matrix Matrix::performCheckerboard(){
  Matrix m(getRows(), getCols());
   for (int i=0; i<getRows(); i++){
      for (int j=0; j<getCols(); j++){
        if (i % 2 == j % 2){
          m.setValue(i,j, getValue(i,j));
        } else { 
          m.setValue(i,j, getValue(i,j) * -1);
        }
      } 
   }
  return m;
}

Matrix Matrix::operator* (Matrix m){
  // TODO: raise exception if cannot be multiplied
  Matrix new_m(getRows(), m.getCols());

  int rows = new_m.getRows();
  int cols = new_m.getCols();
   for (int i=0; i<rows; i++){
      for (int j=0; j<cols; j++){
        float dp = 0;
        for (int r=0; r<rows; r++){
          dp += (getValue(i,r) * m.getValue(r,j));
        }
        new_m.setValue(i,j,dp);
      }
   }
  return new_m;
}

float calcSingleColMatrixMagnitude(Matrix m){
  // TODO: raise exception if not a single col matrix
  // TODO: support single row matrix as well, shorten this f'n name
  float mag_sq = 0;
  for (int c=0; c < m.getCols(); c++){
    mag_sq += m.getValue(0,c) * m.getValue(0,c);
  }
  return sqrt(mag_sq);
}