#ifndef __ALIST_H__
#define __ALIST_H__

typedef struct actionList_t {
  /* public */
  float Duration;
  float TimeElapsed;
  float PercentDone;
  int Blocking;
  int Lanes;
  Vector Actions;
} ALIST;

typedef struct action_t {
  /* public */
  void (* Update)(struct action_t *, float);
  void (* OnStart)(struct action_t *);
  void (* OnEnd)(struct action_t *);
  int IsFinished;
  int IsBlocking;
  unsigned int Lanes;
  float Elapsed;
  float Duration;
  int HasStarted;

  /* private */
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
