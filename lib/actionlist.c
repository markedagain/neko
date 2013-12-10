#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "actionlist.h"

void al_init(ActionList *actionList) {
  actionList->Duration = 0;
  actionList->TimeElapsed = 0.0;
  actionList->PercentDone = 0.0;
  actionList->Blocking = 0;
  actionList->Lanes = 0;
  vector_init(&actionList->Actions);
}

void al_free(ActionList *actionList) {
  vector_free(&actionList->Actions);
}

/* loop through an action list and execute action functions as needed */
void al_update(ActionList *actionList, float deltaTime) {
  int i = 0;
  unsigned int lanes = 0;
  int size = vector_size(&actionList->Actions);
  int actionsFinished = 0;
  int* finished;
  for (i = 0; i < size; ++i) {
    Action *action = (Action *)(vector_get(&actionList->Actions, i));
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

void al_append(ActionList *actionList, Action *action) {
  action->owner = actionList;
  vector_append(&actionList->Actions, (void *)action);
}

Action *al_remove(ActionList *actionList, Action *action) {
  vector_pop(&actionList->Actions, vector_index(&actionList->Actions, (void *)action));
  return NULL; /* needed? */
}

Action *al_begin(ActionList *actionList) {
}

Action *al_end(ActionList *actionList) {
}

int al_isEmpty(ActionList *actionList) {
}

float al_timeLeft(ActionList *actionList) {
}

Action *action_init(Action *action) {
}
