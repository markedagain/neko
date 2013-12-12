#include <stddef.h>
#include <stdlib.h>
#include "vector.h"
#include "actionlist.h"

void al_init(ALIST *actionList) {
  actionList->Duration = 0;
  actionList->TimeElapsed = 0.0;
  actionList->PercentDone = 0.0;
  actionList->Blocking = 0;
  actionList->Lanes = 0;
  vector_init(&actionList->Actions);
}

void al_free(ALIST *actionList) {
  vector_free(&actionList->Actions);
}

/* loop through an action list and execute action functions as needed */
void al_update(ALIST *actionList, float deltaTime) {
  int i = 0;
  unsigned int lanes = 0;
  int size = vector_size(&actionList->Actions);
  int actionsFinished = 0;
  int* finished;
  for (i = 0; i < size; ++i) {
    ACTION *action = (ACTION *)(vector_get(&actionList->Actions, i));
    if (lanes & action->Lanes)
      continue;
    if (!action->HasStarted) {
      action->HasStarted = 1;
      (*(action->OnStart))(action);
    }
    (*(action->Update))(action, deltaTime);
    if (action->IsBlocking)
      lanes |= action->Lanes;

    if (action->IsFinished) {
      (*(action->OnEnd))(action);
      if (!actionsFinished) {
        actionsFinished = 1;
        finished = (int *)calloc(size, sizeof(int));
      }
      finished[i] = 1;
    }
  }
  if (actionsFinished) {
    for (i = size - 1; i >= 0; --i)
      if (finished[i])
        vector_pop(&actionList->Actions, i);
  }
}

void al_append(ALIST *actionList, ACTION *action) {
  action->owner = actionList;
  vector_append(&actionList->Actions, (void *)action);
}

ACTION *al_remove(ALIST *actionList, ACTION *action) {
  vector_pop(&actionList->Actions, vector_index(&actionList->Actions, (void *)action));
  return NULL; /* needed? */
}

ACTION *al_begin(ALIST *actionList) {
}

ACTION *al_end(ALIST *actionList) {
}

int al_isEmpty(ALIST *actionList) {
}

float al_timeLeft(ALIST *actionList) {
}

ACTION *action_init(ACTION *action) {
}
