/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ALIST_H__
#define __ALIST_H__

#include "neko.h"
#include "vector.h"

typedef struct actionList_t {
  float duration;
  float timeElapsed;
  float percentDone;
  int blocking;
  int lanes;
  VECTOR actions;
} ALIST;

typedef struct action_t {
  void (* update)(struct action_t *, float);
  void (* onStart)(struct action_t *);
  void (* onEnd)(struct action_t *);
  int isFinished;
  int isBlocking;
  unsigned int lanes;
  float elapsed;
  float duration;
  int hasStarted;
  ALIST *owner;
} ACTION;

NEKO_API void al_init(ALIST *);
NEKO_API void al_free(ALIST *);
NEKO_API void al_append(ALIST *, ACTION *);
NEKO_API ACTION *al_remove(ALIST *, ACTION *);
NEKO_API ACTION *al_begin(ALIST *);
NEKO_API ACTION *al_end(ALIST *);
NEKO_API int al_isEmpty(ALIST *);
NEKO_API float al_timeLeft(ALIST *);

#endif
