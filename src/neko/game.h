/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __GAME_H__
#define __GAME_H__

#include "linkedlist.h"
#include "util.h"
#include "event.h"

typedef struct space_t SPACE;
typedef struct component_t COMPONENT;

typedef struct game_t {
  LIST *spaces;
  LIST *destroyingEntities;
  LIST *destroyingSpaces;
  unsigned char destroying;
} GAME;

GAME *game_create(void);
void game_destroy(GAME *);
SPACE *game_addSpace(GAME *, char *);
SPACE *game_getSpace(GAME *, char *);
void game_invokeEvent(GAME *, EVENT_TYPE, void *);
void game_update(GAME *);
void game_cleanup(GAME *);

#endif
