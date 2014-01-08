/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"
#include "linkedlist.h"
#include "space.h"
#include "entity.h"
#include "component.h"
#include "event.h"

GAME *game_create(void) {
  GAME *game = malloc(sizeof(GAME));
  game->spaces = list_create();
  game->destroyingEntities = list_create();
  game->destroyingSpaces = list_create();
  game->destroying = 0;
  return game;
}

SPACE *game_addSpace(GAME *game, char *name) {
  SPACE *space = malloc(sizeof(SPACE));
  space->entities = list_create();
  space->game = game;
  strcpy(space->name, name);
  space->active = 1;
  space->visible = 1;
  space->node = list_insert_end(game->spaces, space);
  space->destroying = 0;
  return space;
}

SPACE *game_getSpace(GAME *game, char *name) {
  LIST_NODE *node;

  if (game->spaces->count == 0)
    return NULL;
  node = game->spaces->first;
  while (node != NULL) {
    SPACE *space;
    space = (SPACE *)node->data;
    if (strcmp(name, space->name) == 0)
      return space;
    node = node->next;
  }
  return NULL;
}

void game_invokeEvent(GAME * game, EVENT_TYPE event, void *data) {
  LIST_NODE *spaceNode;

  if (game->spaces->count == 0)
    return;

  spaceNode = game->spaces->first;

  do {
    SPACE *space = (SPACE *)(spaceNode->data);
    LIST_NODE *entityNode;

    if (space->entities->count == 0 || !space->active || space->destroying || (!space->visible && event == EV_DRAW)) {
      spaceNode = spaceNode->next;
      continue;
    }

    entityNode = space->entities->first;

    do {
      ENTITY *entity = (ENTITY *)(entityNode->data);
      unsigned int i = 0;
      unsigned int componentCount = vector_size(&entity->components);

      if (componentCount == 0 || entity->destroying) {
        entityNode = entityNode->next;
        continue;
      }

      do {
        COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);

        if (component->events.logicUpdate == NULL) {
          ++i;
          continue;
        }

        component_doEvent(component, event, data);

        ++i;
      }
      while (i < componentCount - 1);

      entityNode = entityNode->next;
    }
    while (entityNode != NULL);

    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
}

void game_update(GAME *game) {
  EDATA_UPDATE updateEvent = {};
  game_invokeEvent(game, EV_LOGICUPDATE, &updateEvent);
  game_cleanup(game);
}

void game_cleanup(GAME *game) {
  while (game->destroyingEntities->count > 0) {
    ENTITY *entity = (ENTITY *)(game->destroyingEntities->last->data);
    __entity_destroy(entity);
    list_remove(game->destroyingEntities, game->destroyingEntities->last);
  }
  while (game->destroyingSpaces->count > 0) {
    SPACE *space = (SPACE *)(game->destroyingSpaces->last->data);
    __space_destroy(space);
    list_remove(game->destroyingSpaces, game->destroyingSpaces->last);
  }
}
