/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include "entity.h"
#include "space.h"
#include "string.h"
#include "linkedlist.h"

ENTITY *entity_create(SPACE *space, void(*makeFunction)(ENTITY *), char *name) {
  ENTITY *entity = malloc(sizeof(ENTITY));
  entity->id = 0;
  entity->type = 0;
  entity->owner = NULL;
  entity->space = space;
  strcpy(entity->name, name);/*
  vector_init(&entity->tags);
  vector_init(&entity->components);
  vector_init(&entity->children);*/
  entity->destroying = 0;
  makeFunction(entity);
  list_insert_end(space->entities, (void *)entity);
  return entity;
}
