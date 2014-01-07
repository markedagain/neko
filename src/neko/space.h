/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SPACE_H__
#define __SPACE_H__

#include "linkedlist.h"
#include "game.h"

typedef struct space_t {
  char name[32];
  LIST *entities;
  GAME *game;
  unsigned char active;
  unsigned char visible;
  unsigned char destroying;
} SPACE;

SPACE *space_create(GAME *, char *);

#endif
