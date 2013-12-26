/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SPACE_H__
#define __SPACE_H__

#include "vector.h"
#include "game.h"

typedef struct space_t {
  char[32] name;
  VECTOR tags;
  VECTOR entities;
  GAME game;
  unsigned char active;
  unsigned char visible;
  unsigned char shouldDestroy;
} SPACE;

#endif
