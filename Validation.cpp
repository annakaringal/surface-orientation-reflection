#include "Validation.h"

float validRadians(float angle){
  if (angle < 0){
    return validRadians(2*PI - angle);
  }
  else if (angle > 2*PI){
    return validRadians(angle - 2*PI);
  } else {
    return angle;
  }
}