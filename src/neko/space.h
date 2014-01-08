/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SPACE_H__
#define __SPACE_H__

#include "linkedlist.h"
#include "game.h"
#include "entity.h"

typedef struct space_t {
  char name[32];
  LIST *entities;
  GAME *game;
  unsigned char active;
  unsigned char visible;
  LIST_NODE *node;
  unsigned char destroying;
} SPACE;

//SPACE *space_create(GAME *, char *);
ENTITY *space_addEntity(SPACE *, void(*)(ENTITY *), char *);
ENTITY *space_getEntity(SPACE *, char *);
void space_destroy(SPACE *);
void __space_destroy(SPACE *);

#endif
