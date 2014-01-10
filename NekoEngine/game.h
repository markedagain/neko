/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __GAME_H__
#define __GAME_H__

#include "neko.h"
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

NEKO_API GAME *game_create(void);
NEKO_API void game_destroy(GAME *);
NEKO_API SPACE *game_addSpace(GAME *, char *);
NEKO_API SPACE *game_getSpace(GAME *, char *);
NEKO_API void game_invokeEvent(GAME *, EVENT_TYPE, void *);
NEKO_API void game_update(GAME *);
NEKO_API void game_draw(GAME *);
NEKO_API void game_cleanup(GAME *);

#endif