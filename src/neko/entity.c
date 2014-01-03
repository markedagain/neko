/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include "entity.h"
#include "space.h"
#include "string.h"
#include "linkedlist.h"
#include "vector.h"
#include "component.h"

ENTITY *entity_create(SPACE *space, void(*archetypeFunction)(ENTITY *), char *name) {
  ENTITY *entity = malloc(sizeof(ENTITY));
  entity->id = 0;
  entity->type = 0;
  entity->parent = NULL;
  entity->space = space;
  strcpy(entity->name, name);
  vector_init(&entity->tags);
  vector_init(&entity->components);
  vector_init(&entity->children);
  entity->destroying = 0;
  archetypeFunction(entity);
  list_insert_end(space->entities, (void *)entity);
  return entity;
}

void entity_attach(ENTITY *child, ENTITY *parent) {
  child->parent = parent;
  vector_append(&parent->children, child);
}

void entity_connect(ENTITY *entity, void(*componentFunction)(COMPONENT *), void *data) {
  COMPONENT *component = malloc(sizeof(COMPONENT));
  component->owner = entity;
  componentFunction(component);
  component->data = data;
  vector_append(&entity->components, component);
}
