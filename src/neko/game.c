/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
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
  game->destroying = 0;
  return game;
}

SPACE *game_addSpace(GAME *game, char *name) {
  return (SPACE *)(list_insert_end(game->spaces, space_create(game, name))->data);
}

void game_invokeEvent(GAME * game, EVENT_TYPE event, void *data) {
  LIST_NODE *spaceNode;

  if (game->spaces->count == 0)
    return;

  spaceNode = game->spaces->first;

  do {
    SPACE *space = (SPACE *)(spaceNode->data);
    LIST_NODE *entityNode;

    if (space->entities->count == 0 || !space->active || space->destroying) {
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
}
