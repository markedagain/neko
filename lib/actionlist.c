/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stddef.h>
#include <stdlib.h>
#include "vector.h"
#include "actionlist.h"

void al_init(ALIST *actionList) {
  actionList->duration = 0;
  actionList->timeElapsed = 0.0;
  actionList->percentDone = 0.0;
  actionList->blocking = 0;
  actionList->lanes = 0;
  vector_init(&actionList->actions);
}

void al_free(ALIST *actionList) {
  vector_free(&actionList->actions);
}

/* loop through an action list and execute action functions as needed */
void al_update(ALIST *actionList, float deltaTime) {
  int i = 0;
  unsigned int lanes = 0;
  int size = vector_size(&actionList->actions);
  int actionsFinished = 0;
  int* finished;
  for (i = 0; i < size; ++i) {
    ACTION *action = (ACTION *)(vector_get(&actionList->actions, i));
    if (lanes & action->lanes)
      continue;
    if (!action->hasStarted) {
      action->hasStarted = 1;
      (*(action->onStart))(action);
    }
    (*(action->update))(action, deltaTime);
    if (action->isBlocking)
      lanes |= action->lanes;

    if (action->isFinished) {
      (*(action->onEnd))(action);
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
        vector_pop(&actionList->actions, i);
    free(finished);
  }
}

void al_append(ALIST *actionList, ACTION *action) {
  action->owner = actionList;
  vector_append(&actionList->actions, (void *)action);
}

ACTION *al_remove(ALIST *actionList, ACTION *action) {
  vector_pop(&actionList->actions, vector_index(&actionList->actions, (void *)action));
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
