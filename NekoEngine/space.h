/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SPACE_H__
#define __SPACE_H__

#include "neko.h"
#include "linkedlist.h"
#include "game.h"
#include "entity.h"
#include "util.h"
#include "vectormath.h"

typedef struct sysTime_t {
  STOPWATCH stopwatch;
  double dt;
  float scale;
  double currentTime;
} SYS_TIME;

typedef struct sysCamera_t {
  struct {
    VEC3 translation;
    VEC2 scale;
    float rotation;
  } transform;
} SYS_CAMERA;

typedef struct sysSound_t {
  bool positional;
  float volume;
} SYS_SOUND;

typedef struct space_t {
  char name[32];
  LIST *entities;
  struct {
    SYS_TIME time;
    SYS_CAMERA camera;
    SYS_SOUND sound;
  } systems;
  GAME *game;
  unsigned char active;
  unsigned char visible;
  LIST_NODE *node;
  unsigned char destroying;
} SPACE;

NEKO_API SPACE *space_create(char *);
NEKO_API ENTITY *space_addEntity(SPACE *, void(*)(ENTITY *), char *);
NEKO_API ENTITY *space_getEntity(SPACE *, char *);
NEKO_API void space_mouseToWorld(SPACE *, POINT *, POINT *);
NEKO_API void space_destroy(SPACE *);
void space_invokeEvent(SPACE *, EVENT_TYPE, void *);
void space_tick(SPACE *, EDATA_UPDATE *);
void __space_destroy(SPACE *);

#endif
