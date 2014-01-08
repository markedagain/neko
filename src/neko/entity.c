/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "space.h"
#include "string.h"
#include "linkedlist.h"
#include "vector.h"
#include "component.h"

ENTITY *entity_create(SPACE *space, void(*archetypeFunction)(ENTITY *), char *name) {
  ENTITY *entity = malloc(sizeof(ENTITY));
  entity->id = 0;
  entity->parent = NULL;
  entity->space = space;
  strcpy(entity->name, name);
  vector_init(&entity->components);
  vector_init(&entity->children);
  entity->destroying = 0;
  archetypeFunction(entity);
  entity->node = list_insert_end(space->entities, (void *)entity);
  return entity;
}

void entity_attach(ENTITY *child, ENTITY *parent) {
  if (child->destroying || parent->destroying)
    return;
  child->parent = parent;
  vector_append(&parent->children, child);
}

void entity_detach(ENTITY *child, ENTITY *parent) {
  child->parent = NULL;
  vector_remove(&parent->children, child);
}

void *entity_connect(ENTITY *entity, void(*componentFunction)(COMPONENT *)) {
  COMPONENT *component;

  component = malloc(sizeof(COMPONENT));
  component->owner = entity;
  componentFunction(component);

  /* TODO: dependency check */

  vector_append(&entity->components, component);
  return component->data;
}

COMPONENT *entity_getComponent(ENTITY *entity, unsigned int componentId) {
  unsigned int i;
  for (i = 0; i < (int)vector_size(&entity->components); ++i) {
    COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);
    if (component->id == componentId)
      return component;
  }
  return NULL;
}

void *entity_getComponentData(ENTITY *entity, unsigned int componentId) {
  COMPONENT *component;
  component = entity_getComponent(entity, componentId);
  if (component == NULL)
    return NULL;
  return component->data;
}

void entity_destroy(ENTITY *entity) {
  unsigned int childrenCount;
  unsigned int i;
  entity->destroying = 1;
  list_insert_end(entity->space->game->destroyingEntities, entity);
  childrenCount = vector_size(&entity->children);
  for (i = 0; i < childrenCount; ++i) {
    ENTITY *child;
    child = (ENTITY *)vector_get(&entity->children, i);
    entity_detach(child, entity);
    child->destroying = 1;
    list_insert_end(entity->space->game->destroyingEntities, child);
  }
  if (entity->parent != NULL)
    entity_detach(entity, entity->parent);
}

void __entity_destroy(ENTITY *entity) {
  unsigned int i;

  for (i = 0; i < (int)vector_size(&entity->components); ++i) {
    COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);
    if (component == NULL)
      break;
    if (component->events.destroy != NULL)
      (component->events.destroy)(component, NULL);
    free(component->data);
  }
  vector_free(&entity->components);
  vector_free(&entity->children);

  list_remove_free(entity->space->entities, entity->node);
}
