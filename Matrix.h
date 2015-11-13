#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class Matrix{

public:

  Matrix(int rows=1, int cols=3){
    for (int i=0; i<rows; i++){
      vector<int> row;
      for (int j=0; j<cols; j++){
        row.push_back(0);
      }
      matrix.push_back(row);
    }
  };

  Matrix(const Matrix &m){
    int rows = m.getRows();
    int cols = m.getCols();

    for (int i=0; i<rows; i++){
      vector<int> row;
      for (int j=0; j<cols; j++){
        row.push_back(m.getValue(i,j));
      }
      matrix.push_back(row);
    }
  }

  int getRows() const { return getNRows(); };

  int getCols() const { return getNCols(); };

  int getValue(int r, int c) const { return getVal(r,c); };

  void setValue(int r, int c, int v) { setVal(r,c,v); };

  int determinant() { return calcDeterminant(); };

  Matrix scaled(float factor) { return scaleMatrix(); };

  Matrix inverse() { return calcInverse(); };

  // void scaleVectorToLength(int length){ 
  //   scaleVecLength(length); 
  // }


private:

  vector < vector<int> > matrix;

  int getVal(int r, int c) const;

  void setVal(int r, int c, int v);

  int getNRows() const;

  int getNCols() const;

  bool validRow(int r);

  bool validCol(int c);

  int calcDeterminant();

  Matrix scaleMatrix(float factor);

  Matrix calcInverse();

};

float calcSingleColMatrixMagnitude(Matrix m);

// int matrixProduct(int r, vector<Matrix> vec_3x3, Matrix vec_3x1);

#endif