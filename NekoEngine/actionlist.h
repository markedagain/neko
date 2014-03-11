/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ALIST_H__
#define __ALIST_H__

#include "neko.h"
#include "linkedlist.h"
#include "easing.h"

typedef struct actionList_t {
  float duration;
  float timeElapsed;
  float percentDone;
  bool blocking;
  LIST *actions;
} ALIST;

typedef struct action_t {
  void *data;
  void (* update)(struct action_t *, double);
  void (* onStart)(struct action_t *);
  void (* onEnd)(struct action_t *);
  bool isFinished;
  bool isBlocking;
  float elapsed;
  float duration;
  bool hasStarted;
  ALIST *owner;
  LIST_NODE *node;
} ACTION;

typedef void (* ACTION_UPDATE)(ACTION *, double deltaTime);
typedef void (* ACTION_ONSTART)(ACTION *);
typedef void (* ACTION_ONEND)(ACTION *);

NEKO_API void al_init(ALIST *);
NEKO_API void al_destroy(ALIST *);
NEKO_API void al_update(ALIST *, double deltaTime);
NEKO_API void al_pushFront(ALIST *actionList, ACTION *action);
NEKO_API void al_pushBack(ALIST *actionList, ACTION *action);
NEKO_API void al_insertBefore(ALIST *actionList, ACTION *afterAction, ACTION *action);
NEKO_API void al_insertAfter(ALIST *actionList, ACTION *beforeAction, ACTION *action);
NEKO_API ACTION *al_remove(ALIST *, ACTION *);
NEKO_API ACTION *al_begin(ALIST *);
NEKO_API ACTION *al_end(ALIST *);
NEKO_API int al_isEmpty(ALIST *);
NEKO_API void al_clear(ALIST *);

NEKO_API ACTION *action_create(void *data, ACTION_UPDATE update, ACTION_ONSTART onStart, ACTION_ONEND onEnd, bool blocking, float duration);
NEKO_API float action_ease(ACTION *action, EASING easing, float startValue, float endValue);
NEKO_API float action_getEase(ACTION *action, EASING easing);

#endif
