/******************************************************************************
Filename: random.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include <time.h>
#include <stdlib.h>
#include "random.h"

int randomIntRange(int a, int b) {
  int value, c;

  if (b < a)
    return 0;

  if (a == b)
    return a;

  c = b - a;

  value = rand() % (c + 1) + a;
  return value;
 }
 
float randomFloatRange(float a, float b) {
  return ( (b - a) * ( (float)rand() / RAND_MAX) ) + a;
}