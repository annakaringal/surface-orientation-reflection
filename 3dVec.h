#ifndef 3D_VEC
#define 3D_VEC

#include <iostream>
#include <math.h>

using namespace std;

class 3dVec{

public:

  3dVec(int a=0, int b=0, int c=0) : x(a), y(b), z(c) { };

  void setX(int new_x){ x = new_x };
  void setY(int new_y){ y = new_y };
  void setZ(int new_z){ z = new_z };

  int getX(){ return x; };
  int getY(){ return y; };
  int getZ(){ return z; };

  void scaleVectorToLength(int length){ 
    scaleVecLength(length); 
  }

  float magnitude() { return calcMagnitude(); };

private:
  int x, y, z;

  float calcMagnitude();

  void scaleVecLength(int length);
};

vector <3dVec> invert(vector<3dVec> 3x3_vec);

int matrixProduct(int r, vector<3dVec> 3x3_vec, 3dVec 3x1_vec);

#endif