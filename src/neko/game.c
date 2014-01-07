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
  game->destroying = 0;
  return game;
}

SPACE *game_addSpace(GAME *game, char *name) {
  return (SPACE *)(list_insert_end(game->spaces, space_create(game, name))->data);
}

void game_update(GAME *game) {
  EDATA_UPDATE updateEvent = {};
  LIST_NODE *spaceNode;

  if (game->spaces->count == 0)
    return;

  spaceNode = game->spaces->first;

  do {
    SPACE *space = (SPACE *)(spaceNode->data);
    LIST_NODE *entityNode;

    if (space->entities->count == 0)
      continue;

    entityNode = space->entities->first;

    do {
      ENTITY *entity = (ENTITY *)(entityNode->data);
      unsigned int i = 0;
      unsigned int entityCount = vector_size(&entity->components);

      if (entityCount == 0)
        continue;

      do {
        COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);

        if (component->events.logicUpdate == NULL)
          continue;

        component->events.logicUpdate(component, &updateEvent);

        ++i;
      }
      while (i < entityCount - 1);

      entityNode = entityNode->next;
    }
    while (entityNode != NULL);

    spaceNode = spaceNode->next;
  }
  while (spaceNode != NULL);
}
