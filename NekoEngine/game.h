/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __GAME_H__
#define __GAME_H__

#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "neko.h"
#include "linkedlist.h"
#include "util.h"
#include "event.h"
#include "input.h"
#include "../AlphaEngine/AEEngine.h"

typedef struct space_t SPACE;
typedef struct component_t COMPONENT;

typedef struct game_t {
  LIST *spaces;
  LIST *destroyingEntities;
  LIST *destroyingSpaces;
  struct {
    unsigned int width;
    unsigned int height;
  } window;
  INPUT_CONTAINER input;
  unsigned char destroying;
} GAME;

NEKO_API GAME *game_create(HINSTANCE, int);
NEKO_API void game_destroy(GAME *);
NEKO_API SPACE *game_addSpace(GAME *, char *);
NEKO_API SPACE *game_getSpace(GAME *, char *);
void game_invokeEvent(GAME *, EVENT_TYPE, void *);
void game_getInput(GAME *);
void game_update(GAME *);
void game_draw(GAME *);
void game_cleanup(GAME *);
NEKO_API void game_start(GAME *);
bool game_loop(GAME *);

#endif
