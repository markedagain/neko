#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__

typedef struct actionList_t {
  /* public */
  float Duration;
  float TimeElapsed;
  float PercentDone;
  int Blocking;
  int Lanes;
  Vector Actions;
} ActionList;

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
  ActionList *owner;
} Action;

void al_init(ActionList *);
void al_free(ActionList *);
void al_append(ActionList *, Action *);
Action *al_remove(ActionList *, Action *);
Action *al_begin(ActionList *);
Action *al_end(ActionList *);
int al_isEmpty(ActionList *);
float al_timeLeft(ActionList *);

#endif
