/******************************************************************************
Filename: colors.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COLORS_H__
#define __COLORS_H__

#include "vectormath.h"

typedef enum {
  C_TURQUOISE_LIGHT,
  C_TURQUOISE_DARK,
  C_GREEN_LIGHT,
  C_GREEN_DARK,
  C_BLUE_LIGHT,
  C_BLUE_DARK,
  C_PURPLE_LIGHT,
  C_PURPLE_DARK,
  C_NAVY_LIGHT,
  C_NAVY_DARK,
  C_YELLOW_LIGHT,
  C_YELLOW_DARK,
  C_ORANGE_LIGHT,
  C_ORANGE_DARK,
  C_RED_LIGHT,
  C_RED_DARK,
  C_WHITE_LIGHT,
  C_WHITE_DARK,
  C_GRAY_LIGHT,
  C_GRAY_DARK,
  C_LAST
} NAMEDCOLOR;

VEC4 colors[C_LAST];

#endif