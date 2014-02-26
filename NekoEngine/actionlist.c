/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stddef.h>
#include <stdlib.h>
#include "actionlist.h"

void al_init(ALIST *actionList) {
  actionList->duration = 0;
  actionList->timeElapsed = 0.0;
  actionList->percentDone = 0.0;
  actionList->blocking = 0;
  actionList->lanes = 0;
  actionList->actions = list_create();
}

void al_free(ALIST *actionList) {
  list_destroy(actionList->actions);
}

/* loop through an action list and execute action functions as needed */
void al_update(ALIST *actionList, float deltaTime) {
  int i = 0;
  unsigned int lanes = 0;
  int size = actionList->actions->count;
  int actionsFinished = 0;
  int* finished = NULL;
  for (i = 0; i < size; ++i) {
    ACTION *action = (ACTION *)(list_get(actionList->actions, i));
    if (lanes & action->lanes)
      continue;
    if (!action->hasStarted) {
      action->hasStarted = 1;
      if (action->onStart)
        (*(action->onStart))(action);
    }
    action->elapsed += deltaTime;
    if (action->update)
      (*(action->update))(action, deltaTime);
    if (action->elapsed >= action->duration)
      action->isFinished = true;
    if (action->isBlocking)
      lanes |= action->lanes;

    if (action->isFinished) {
      if (action->onEnd)
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
        list_removeAt(actionList->actions, i);
    free(finished);
  }
}

void al_pushFront(ALIST *actionList, ACTION *action) {
  LIST_NODE *node = list_insert_beginning(actionList->actions, action);
  action->owner = actionList;
  action->node = node;
}

void al_pushBack(ALIST *actionList, ACTION *action) {
  LIST_NODE *node = list_insert_beginning(actionList->actions, action);
  action->owner = actionList;
  action->node = node;
}

void al_insertBefore(ALIST *actionList, ACTION *afterAction, ACTION *action) {
  LIST_NODE *afterNode = list_getNode(actionList->actions, afterAction);
  LIST_NODE *node;

  if (afterNode == NULL)
    return;

  node = list_insert_before(actionList->actions, afterNode, action);
  action->owner = actionList;
  action->node = node;
}

void al_insertAfter(ALIST *actionList, ACTION *beforeAction, ACTION *action) {
  LIST_NODE *beforeNode = list_getNode(actionList->actions, beforeAction);
  LIST_NODE *node;

  if (beforeNode == NULL)
    return;

  node = list_insert_after(actionList->actions, beforeNode, action);
  action->owner = actionList;
  action->node = node;
}

ACTION *al_remove(ALIST *actionList, ACTION *action) {
  return (ACTION *)list_remove(actionList->actions, action->node);
}

ACTION *al_begin(ALIST *actionList) {
  return (ACTION *)actionList->actions->first->data;
}

ACTION *al_end(ALIST *actionList) {
  return (ACTION *)actionList->actions->last->data;
}

int al_isEmpty(ALIST *actionList) {
  return actionList->actions->count == 0;
}

float al_timeLeft(ALIST *actionList) {
  return 0;
}

ACTION *action_create(void *data, ACTION_UPDATE update, ACTION_ONSTART onStart, ACTION_ONEND onEnd, int lanes, float duration) {
  ACTION *action = (ACTION *)malloc(sizeof(ACTION));
  action->data = data;
  action->update = update;
  action->onStart = onStart;
  action->onEnd = onEnd;
  action->isBlocking = false;
  action->isFinished = false;
  action->lanes = lanes;
  action->elapsed = 0.0f;
  action->duration = duration;
  action->hasStarted = false;
  action->owner = NULL;
  action->node = NULL;
  return action;
}

float action_ease(ACTION *action, EASING easing, float startValue, float endValue) {
  return (*(easings[easing]))(action->elapsed, startValue, endValue, action->duration);
}