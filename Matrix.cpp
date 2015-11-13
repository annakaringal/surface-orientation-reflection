#include "Matrix.h"

int Matrix::getVal(int r, int c){ return matrix[r][c]; }

void Matrix::setVal(int r, int c, int v){
  if (validRow(r) && validCol(c)) {
    matrix[r][c] = v;
  }
}

int Matrix::getNRows() const { return matrix.size(); }

int Matrix::getNCols() const {
  return (getNRows() > 0 ? matrix[0].size(): 0);
}

bool Matrix::validRow(int r){ return r >= 0 && r < getNRows(); }

bool Matrix::validCol(int c){ return c >= 0 && c < getNCols(); }

int Matrix::calcDeterminant(){

  int det = 0;
  int rows = getRows();
  int cols = getCols();

  // Base case: 1x1 and 2x2 matrix
   if (rows == 1 && cols == 1){
    return getValue(0,0);
  } else if (rows == 2 && cols == 2){ 
    int a,b,c,d; 
    a = getValue(0,0);
    b = getValue(0,1);
    c = getValue(1,0);
    d = getValue(1,1);

    return a*d - b*c;
  } else {
    for (int c=0; c<cols; c++){
      Matrix m(rows-1, cols-1);
      for (int i=1; i<rows; i++){
        for (int j=0; j<cols; j++){
          if (j != c){
            m.setValue(i,j,getValue(i,j));
          }
        }
      }

      if (c % 2 == 0 ){
        det += getValue(0,c) * m.calcDeterminant();
      } else { 
        det -= getValue(0,c) * m.calcDeterminant();
      }
    }
    return det; 
  }
}

Matrix Matrix::scaleMatrix(float factor){
  Matrix new_m(rows(), cols());
   for (int i=0; i<rows(); i++){
      for (int j=0; j<cols(); j++){
        new_m.setValue(i,j, getValue(i,j) * factor);
      }
   }
  return new_m;
}

Matrix Matrix::calcInverse(){ 
  Matrix inverse(rows(), cols());

  return inverse * determinant();
}

int calcSingleColMatrixMagnitude(Matrix m){
  float mag_sq = 0;
  for (int r=0; r<m.rows(); r++){
    mag_sq += m.getValue(r,0) * m.getValue(r,0);
  }
  return sqrt(mag_sq);
}

// int matrixProduct(int r, vector<Matrix> vec_3x3, Matrix vec_3x1){
//   int prod = vec_3x3[r].getX() * vec_3x1.getX();
//   prod += vec_3x3[r].getY() * vec_3x1.getY();
//   prod += vec_3x3[r].getZ() * vec_3x1.getZ();
//   return prod;
// }