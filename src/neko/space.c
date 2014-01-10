/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "game.h"
#include "linkedlist.h"
#include "vector.h"
#include "entity.h"

/*SPACE *space_create(GAME *game, char *name) {
  SPACE *space = malloc(sizeof(SPACE));
  space->entities = list_create();
  space->game = game;
  strcpy(space->name, name);
  space->active = 1;
  space->visible = 1;
  space->node = NULL;
  space->destroying = 0;
  return space;
}*/

ENTITY *space_addEntity(SPACE *space, void (*archetypeFunction)(ENTITY *), char *name) {
  ENTITY *entity = (ENTITY *)malloc(sizeof(ENTITY));
  int componentCount;
  entity->id = 0;
  entity->parent = NULL;
  entity->space = space;
  strcpy(entity->name, name);
  vector_init(&entity->components);
  vector_init(&entity->children);
  entity->destroying = 0;
  if (archetypeFunction != NULL)
    archetypeFunction(entity);
  componentCount = vector_size(&entity->components);
  if (componentCount > 0) {
    int i;
    for (i = 0; i < componentCount; ++i) {
      COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);
      if (component->events.initialize != NULL)
        component->events.initialize(component, NULL);
    }
  }
  entity->node = list_insert_end(space->entities, (void *)entity);
  return entity;
}

ENTITY *space_getEntity(SPACE *space, char *name) {
  LIST_NODE *node;
  if (space->entities->count == 0)
    return NULL;
  node = space->entities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (strcmp(entity->name, name) == 0)
      return entity;
    node = node->next;
  }
  return NULL;
}

void space_destroy(SPACE *space) {
  LIST_NODE *node;
  space->destroying = 1;
  list_insert_end(space->game->destroyingSpaces, space);
  if (space->entities->count == 0)
    return;
  node = space->entities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (entity->destroying) {
      node = node->next;
      continue;
    }
    node = node->next;
    entity_destroy(entity);
  }
}

void __space_destroy(SPACE *space) {
  list_destroy(space->entities);
  list_remove_free(space->game->spaces, space->node);
}
