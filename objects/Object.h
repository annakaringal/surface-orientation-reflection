#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <math.h>

#include "../pgm/Image.h"
#include "../Validation.h"

#define PI 3.14159265

using namespace std;

class Object{

public:
  Object(int l, int a=0, int xS=0, int yS=0, int xxS=0, int yyS=0, int xy=0)
        : label(l), area(a), xSum(xS), ySum(yS), xSqSum(xxS), ySqSum(yyS), xySum(xy){};

  // Given x and y coordinates of pixel, update the xSum, ySum, 
  // xSqSum, xSqSum and xySum of the object so propertie can be calculated
  // in one scan.
  void updateXYProperties(int x, int y);

  // Calculates center coordinates and sets member variables
  // Precondition: full scan has been preformed to update xSum, ySum of object
  pair<float,float> calculateCenter();

  // Calculates center coordinates and sets member variables
  // Precondition: full scan has been preformed to update xSum, ySum of object
  void calculateOrientation();

  // Calculates orientation properties (min/max angle, min/max momentum, orientation line,
  // roundness) and sets member variables
  // Precondition: full scan has been preformed to update/calculate xSqSum, ySqSum,
  // xySum and center coordinates.
  void calculateOrientationLine();

  // Get object attributes
  int getLabel() const { return label; };

  int getArea() const { return area; };

  pair<float, float> getOrientation() const { return orientation_line; };

  float getMinMoment() const { return min_moment; };

  float getRoundness() const { return roundness; };

  pair<float,float> getCenter() const {
    return pair<float, float> (centerRow, centerCol);
  };

  // Set object attributes
  void setCenter(float r, float c);

  void setArea(int a);

  void setMinAngle(float minA);

  void setMinMoment(float minM);

  void setRoundness(float r);

private:
  int label;
  float centerRow, centerCol;
  float min_moment, max_moment;
  float min_angle, max_angle;
  float roundness;
  pair <float, float> orientation_line;
  int area;
  int xSum, ySum;
  int xSqSum, ySqSum; 
  int xySum;

  float calculateMoment(float a, float b, float c, float angle);
};


#endif