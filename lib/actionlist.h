/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __ALIST_H__
#define __ALIST_H__

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

void al_init(ALIST *);
void al_free(ALIST *);
void al_append(ALIST *, ACTION *);
ACTION *al_remove(ALIST *, ACTION *);
ACTION *al_begin(ALIST *);
ACTION *al_end(ALIST *);
int al_isEmpty(ALIST *);
float al_timeLeft(ALIST *);

#endif
