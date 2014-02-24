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
  LIST *newEntities;
  LIST *createdEntities;
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

NEKO_API SPACE *space_create(char *name);
NEKO_API ENTITY *space_addEntity(SPACE *space, void(*)(ENTITY *archetypeFunction), char *name);
NEKO_API ENTITY *space_addEntityAtPosition(SPACE *space, void (*archetypeFunction)(ENTITY *), char *name, VEC3 *position);
NEKO_API ENTITY *space_getEntity(SPACE *space, char *name);
NEKO_API void space_getAllEntities(SPACE *space, char *name, LIST *list);
NEKO_API void space_mouseToWorld(SPACE *space, POINT *mousePos, POINT *worldPos);
NEKO_API void space_destroy(SPACE *space);
NEKO_API void space_getCamTranslate(SPACE *space, VEC3 *camTranslate);
void space_invokeEvent(SPACE *space, EVENT_TYPE event, void *data);
void space_invokeEventReverseways(SPACE *space, EVENT_TYPE event, void *data);
void space_tick(SPACE *space, EDATA_UPDATE *data, EDATA_UPDATE *logicData, bool logicUpdate);
void __space_destroy(SPACE *space);

#endif
