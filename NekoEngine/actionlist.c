/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stddef.h>
#include <stdlib.h>
#include "actionlist.h"

void al_init(ALIST *actionList) {
  actionList->duration = 0;
  actionList->timeElapsed = 0.0;
  actionList->percentDone = 0.0;
  actionList->blocking = 0;
  actionList->actions = list_create();
}

void al_destroy(ALIST *actionList) {
  LIST_NODE *node = actionList->actions->first;
  while (node) {
    ACTION *action = (ACTION *)node->data;
    if (action->hasStarted && action->onEnd)
      (*action->onEnd)(action);
    free(action);
    node = node->next;
  }
  list_destroy(actionList->actions);
}

/* loop through an action list and execute action functions as needed */
void al_update(ALIST *actionList, float deltaTime) {
  int i = 0;
  int size = actionList->actions->count;
  int actionsFinished = 0;
  LIST *finished = NULL;
  ACTION *action = al_begin(actionList);
  while (action) {
    if (!action->hasStarted) {
      action->hasStarted = true;
      if (action->onStart)
        (*(action->onStart))(action);
    }
    action->elapsed += deltaTime;
    if (action->update)
      (*(action->update))(action, deltaTime);
    if (action->elapsed >= action->duration)
      action->isFinished = true;

    if (action->isFinished) {
      if (action->onEnd)
        (*(action->onEnd))(action);
      if (!actionsFinished)
        finished = list_create();
      ++actionsFinished;
      list_insert_end(finished, action);
    }
    if (action->isBlocking && !action->isFinished)
      break;
    if (!action->node->next)
      break;
    action = (ACTION *)action->node->next->data;
  }
  if (finished) {
    LIST_NODE *node = finished->first;
    while (node) {
      ACTION *a = (ACTION *)node->data;
      free(al_remove(actionList, a));
      node = node->next;
    }
    list_destroy(finished);
  }
}

void al_pushFront(ALIST *actionList, ACTION *action) {
  LIST_NODE *node = list_insert_beginning(actionList->actions, action);
  action->owner = actionList;
  action->node = node;
}

void al_pushBack(ALIST *actionList, ACTION *action) {
  LIST_NODE *node = list_insert_end(actionList->actions, action);
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
  return actionList->actions->count == 0 ? NULL : (ACTION *)actionList->actions->first->data;
}

ACTION *al_end(ALIST *actionList) {
  return actionList->actions->count == 0 ? NULL : (ACTION *)actionList->actions->last->data;
}

int al_isEmpty(ALIST *actionList) {
  return actionList->actions->count == 0;
}

ACTION *action_create(void *data, ACTION_UPDATE update, ACTION_ONSTART onStart, ACTION_ONEND onEnd, bool blocking, float duration) {
  ACTION *action = (ACTION *)malloc(sizeof(ACTION));
  action->data = data;
  action->update = update;
  action->onStart = onStart;
  action->onEnd = onEnd;
  action->isBlocking = blocking;
  action->isFinished = false;
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

float action_getEase(ACTION *action, EASING easing) {
  return action_ease(action, easing, 0.0f, 1.0f);
}