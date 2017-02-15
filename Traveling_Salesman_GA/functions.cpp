#include "functions.h"

#include <stdlib.h>

//  Name: RandomFloat
//  Purpose: Generate a random float between min and max
//  Inputs: float min representing the lower bound
//  float max representing the upper bound
//  Outputs: A random float between min and max
float RandomFloat(float min, float max) {
  float f = (float)rand() / RAND_MAX;
  return min + f * (max - min);
}