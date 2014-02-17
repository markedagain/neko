/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <time.h>
#include <stdlib.h>
#include "random.h"

int randomIntRange(int a, int b) {
  int value, c;
  
  if (a == 0) {
    value = rand() % b + 1;
    return value;
    }
  else {
    c = b - a;
    value = rand() % c + a + 1;
    return value;
    }
 }
 
float randomFloatRange(float a, float b) {
  return ( (b - a) * ( (float)rand() / RAND_MAX) ) + a;
}