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
      vector<float> row;
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
      vector<float> row;
      for (int j=0; j<cols; j++){
        row.push_back(m.getValue(i,j));
      }
      matrix.push_back(row);
    }
  }

  int getRows() const { return getNRows(); };

  int getCols() const { return getNCols(); };

  float getValue(int r, int c) const { return getVal(r,c); };

  void setValue(int r, int c, int v) { setVal(r,c,v); };

  float determinant() { return calcDeterminant(); };

  Matrix inverse() { return calcInverse(); };

  Matrix cofactor() { return calcCofactor(); };

  Matrix adjugate() { return calcAdjugate(); };

  Matrix transpose() { return calcTranspose(); };

  Matrix minors() { return calcMinors(); };

  Matrix checkerboard() { return performCheckerboard(); };

  Matrix operator* (float x);

  Matrix operator* (Matrix m);

private:

  vector < vector<float> > matrix;

  float getVal(int r, int c) const;

  void setVal(int r, int c, float v);

  int getNRows() const;

  int getNCols() const;

  bool validRow(int r);

  bool validCol(int c);

  float calcDeterminant();

  Matrix calcInverse();

  Matrix calcCofactor();

  Matrix calcAdjugate();

  Matrix calcTranspose();

  Matrix calcMinors();

  Matrix performCheckerboard();

  float getMinor(int r, int c);

};

Matrix checkerboardMatrix(int rows, int cols);

float calcSingleColMatrixMagnitude(Matrix m);

#endif