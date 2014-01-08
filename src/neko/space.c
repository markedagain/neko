/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
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
  LIST_NODE *node;
  space->destroying = 1;
  list_insert_end(space->game->destroyingSpaces, space);
  if (space->entities->count == 0)
    return;
  node = space->entities->first;
  while (node != NULL) {
    LIST_NODE *next;
    ENTITY *entity = (ENTITY *)node->data;
    printf("DESTROYING %s\n", entity->name);
    if (entity->destroying) {
      node = node->next;
      continue;
    }
    //entity_destroy(entity);
    next = node->next;
    //list_remove(space->entities, node);
    node = next;
    entity_destroy(entity);
  }
}

void __space_destroy(SPACE *space) {
  printf("Entities I fucked up and forgot to delete: %i\n", space->entities->count);
  list_destroy(space->entities);
  list_remove_free(space->game->spaces, space->node);
}
