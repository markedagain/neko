/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "game.h"
#include "linkedlist.h"
#include "entity.h"

SPACE *space_create(GAME *game, char *name) {
  SPACE *space = malloc(sizeof(SPACE));
  space->entities = list_create();
  space->game = game;
  strcpy(space->name, name);
  space->active = 1;
  space->visible = 1;
  space->node = NULL;
  space->destroying = 0;
  return space;
}

void space_destroy(SPACE *space) {
  space->destroying = 1;
  list_insert_end(space->game->destroyingSpaces, space);
  while (space->entities->count > 0) {
    ENTITY *entity = (ENTITY *)space->entities->last->data;
    if (entity->destroying)
      continue;
    entity->space = NULL;
    entity_destroy(entity);
    list_remove(space->entities, space->entities->last);
  }
}

void __space_destroy(SPACE *space) {
  list_destroy(space->entities);
  list_remove_free(space->game->spaces, space->node);
}
