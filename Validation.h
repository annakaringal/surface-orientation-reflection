#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <sstream>

#define PI 3.14159265

using namespace std;

// Convert angle in radians to value between 0 and 2*PI
// Precondition: angle is in Radians
// Returns the equivalent value of original angle within 0 and 2*PI
float validRadians(float angle);

// Check if typename S can be cast to typename T
template<typename T, typename S> bool isValidType(const S str){
  istringstream ss(str);
  T f;
  ss >> noskipws >> f;
  return ss.eof() && !ss.fail(); 
}

#endif