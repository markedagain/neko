/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __GAME_H__
#define __GAME_H__

#include "linkedlist.h"
#include "util.h"

typedef struct space_t SPACE;

typedef struct game_t {
  LIST *spaces;
  unsigned char destroying;
} GAME;

GAME *game_create(void);
void game_destroy(GAME *);
SPACE *game_addSpace(GAME *, char *);
void game_update(GAME *);

#endif
