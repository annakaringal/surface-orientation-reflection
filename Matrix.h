/*****************************************************************************
 Title:             Matrix.h
 Author:            Anna Cristina Karingal
 Created on:        November 13, 2015
 Description:       Matrix class with some matrix operations
 
 Last Modified:     November 14, 2015
 *****************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// Matrix class containing floats
//
// CONSTRUCTION: - given row & col, rowxcol matrix full of 0's
//               - copy constructor
//
// ******************PUBLIC OPERATIONS*********************
// int getRows()        --> returns number of rows in matrix
// int getCols()        --> returns number of columns in matrix
// float getValue(r,c)  --> returns value at row r, col c
// void setValue(r,c,v) --> sets value at row r, col c to v
// float determinant()  --> returns determinant of matrix
// Matrix inverse()     --> returns new matrix that is inverse of matrix
// Matrix cofactor()    --> returns new matrix that is cofactor of matrix
// Matrix transpose()   --> returns new matrix that is transpose of matrix
// Matrix minors()      --> returns new matrix that is matrix of minors of matrix
// Matrix checkerboard()--> returns new matrix that applies checkerboard pattern
//                           to matrix
// ***************** overloaded operators *****************
// Matrix *(f)          --> returns matrix scaled by f
// Matrix *(m)          --> returns matrix product of matrix and m

class Matrix{

public:

  // EMPTY MATRIX CONSTRUCTOR
  Matrix(int rows=1, int cols=3){
    for (int i=0; i<rows; i++){
      vector<float> row;
      for (int j=0; j<cols; j++){
        row.push_back(0);
      }
      matrix.push_back(row);
    }
  };

  // COPY CONSTRUCTOR
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

  // PUBLIC GETTERS
  int getRows() const { return getNRows(); };

  int getCols() const { return getNCols(); };

  float getValue(int r, int c) const { return getVal(r,c); };

  // PUBLIC SETTER
  void setValue(int r, int c, float v) { setVal(r,c,v); };

  // CALCULATES & TRANSFORMS PROPERTIES OF MATRIX
  float determinant() { return calcDeterminant(); };

  Matrix inverse() { return calcInverse(); };

  Matrix cofactor() { return calcCofactor(); };

  Matrix transpose() { return calcTranspose(); };

  Matrix minors() { return calcMinors(); };

  Matrix checkerboard() { return performCheckerboard(); };

  // OVERLOAD * OPERATOR TO SUPPORT SCALING AND MATRIX PRODUCT
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

  Matrix calcMinors();

  float getMinor(int r, int c);

  Matrix calcTranspose();

  Matrix performCheckerboard();

};

// Returns magnitude of a single row or single column matrix
float magnitude(Matrix m);

#endif