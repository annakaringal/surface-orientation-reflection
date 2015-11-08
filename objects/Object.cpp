#include "Object.h"

void Object::updateXYProperties(int x, int y){
  area++;
  xSum += x; 
  ySum += y;
  xSqSum += (x*x);
  ySqSum += (y*y);
  xySum += (x*y);
};

pair<float,float> Object::calculateCenter(){
  if (area > 0) {
    centerRow = xSum / area;
    centerCol = ySum / area;
  } else {
    centerRow = 0;
    centerCol = 0;
  }
  return pair<float,float> (centerRow, centerCol);
}

void Object::calculateOrientation(){
  float a = xSqSum - (centerRow * centerRow * area);
  float b = xySum - (2 * centerRow * centerCol * area);
  float c = ySqSum - (centerCol * centerCol * area);

  if (b!=0 && a!=c){
    min_angle = validRadians(atan((2*b) / (a-c))) / 2;
  } else { 
    min_angle = 0;
  }
  max_angle = validRadians((PI / 2) + min_angle);

  min_moment = calculateMoment(a, b, c, min_angle);
  max_moment = calculateMoment(a, b, c, max_angle);

  roundness = min_moment / max_moment;

  calculateOrientationLine();

}

float Object::calculateMoment(float a, float b, float c, float angle){
  return (a*sin(angle)*sin(angle)) - (b*sin(angle)*cos(angle)) + (c*cos(angle)*cos(angle));
}

void Object::calculateOrientationLine(){
  orientation_line.first = (centerCol*cos(min_angle)) - (centerRow*sin(min_angle));
  orientation_line.second = min_angle;
}

void Object::setCenter(float r, float c){
  centerRow = r; 
  centerCol = c;
}

void Object::setArea(int a){ area = a; }

void Object::setMinAngle(float minA){ min_angle = minA; }

void Object::setMinMoment(float minM){ min_moment = minM; }

void Object::setRoundness(float r){ roundness = r; }