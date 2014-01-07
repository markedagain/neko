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
  list_insert_end(space->entities, (void *)entity);
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

int __entity_idEquals(void *entity, void *id) {
  return ((ENTITY *)(entity))->id == *((int *)id);
}

void entity_destroy(ENTITY *entity) {
  entity->destroying = 1;
  list_insert_end(entity->space->game->destroyingEntities, entity);
}

void __entity_destroy(ENTITY *entity) {
  unsigned int i;
  LIST_NODE *node;
  
  if (entity->parent != NULL) {
    entity_detach(entity, entity->parent);
  }
  if (vector_size(entity->children) > 0) {
    unsigned int j;
    unsigned int childrenCount = vector_size(entity->children);
    for (j = 0; j < childrenCount; ++j) {
      entity_detach(vector_get(entity->children, j), entity);
    }
  }
  
  for (i = 0; i < (int)vector_size(&entity->components); ++i) {
    COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);
    if (component == NULL)
      break;
    if (component->events.destroy == NULL)
      break;
    (component->events.destroy)(component, NULL);
    free(component->data);
  }
  node = list_find(entity->space->entities, __entity_idEquals, &entity->id);
  list_remove(entity->space->entities, node);
  free(node->data);
}