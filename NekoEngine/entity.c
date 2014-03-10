/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "space.h"
#include "string.h"
#include "linkedlist.h"
#include "vector.h"
#include "component.h"

ENTITY *entity_create(void(*archetypeFunction)(ENTITY *), char *name)
 {
  ENTITY *entity = (ENTITY *)malloc(sizeof(ENTITY));
  int i;
  entity->id = 0;
  entity->parent = NULL;
  entity->space = NULL;
  entity->name[0] = 0;
  for (i = 0; i < EV_LAST; ++i)
    entity->handled[i] = false;
  if (name != NULL)
    strcpy(entity->name, name);
  vector_init(&entity->components);
  vector_init(&entity->children);
  entity->destroying = 0;
  if (archetypeFunction != NULL)
    archetypeFunction(entity);
  entity->node = NULL;
  return entity;
}

void entity_attach(ENTITY *child, ENTITY *parent) {
  EDATA_UPDATE logicUpdateEvent = { 0 };
  logicUpdateEvent.dt = child->space->game->systems.time.dt;
  if (child->destroying || parent->destroying)
    return;
  child->parent = parent;
  vector_append(&parent->children, child);
  entity_invokeEvent(child, EV_LOGICUPDATE, &logicUpdateEvent);
}

void entity_detach(ENTITY *child, ENTITY *parent) {
  child->parent = NULL;
  vector_remove(&parent->children, child);
}

void *entity_connect(ENTITY *entity, void(*componentFunction)(COMPONENT *)) {
  COMPONENT *component;

  component = (COMPONENT *)malloc(sizeof(COMPONENT));
  component->owner = entity;
  component->data = NULL;
  componentFunction(component);

  /* TODO: dependency check */

  vector_append(&entity->components, component);
  return component->data;
}

COMPONENT *entity_getComponent(ENTITY *entity, unsigned int componentId) {
  unsigned int i;
  size_t componentCount = vector_size(&entity->components);
  for (i = 0; i < componentCount; ++i) {
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

void entity_invokeEvent(ENTITY *entity, EVENT_TYPE event, void *data) {
  unsigned int i = 0;
  unsigned int componentCount = vector_size(&entity->components);

  if (componentCount == 0 || entity->destroying || entity->handled[event]) {
    entity->handled[event] = true;
    return;
  }
  while (i < componentCount) {
    COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);

    if (component->events.ids[event] == NULL) {
      ++i;
      continue;
    }
    component_doEvent(component, event, data);
    ++i;
  }
}

void entity_destroy(ENTITY *entity) {
  //unsigned int childrenCount;
  //unsigned int i;
  if (entity->destroying)
    return;
  entity->destroying = 1;
  list_insert_end(entity->space->game->destroyingEntities, entity);
  /*childrenCount = vector_size(&entity->children);
  for (i = 0; i < childrenCount; ++i) {
    ENTITY *child;
    child = (ENTITY *)vector_get(&entity->children, i);
    if (child->destroying)
      continue;
    entity_detach(child, entity);
    child->destroying = 1;
    if (entity->space != NULL)
      list_insert_end(entity->space->game->destroyingEntities, child);
  }*/
  while (vector_size(&entity->children) > 0) {
    ENTITY *child;
    child = (ENTITY *)vector_get(&entity->children, 0);
    if (child->destroying)
      continue;
    //entity_detach(child, entity);
    //child->destroying = 1;
    entity_destroy(child);
    /*if (entity->space != NULL)
      list_insert_end(entity->space->game->destroyingEntities, child);*/
  }
  if (entity->parent != NULL)
    entity_detach(entity, entity->parent);
}

void __entity_destroy(ENTITY *entity) {
  unsigned int i;
  size_t componentCount = vector_size(&entity->components);

  for (i = 0; i < componentCount; ++i) {
    COMPONENT *component = (COMPONENT *)vector_get(&entity->components, i);
    if (component == NULL)
      break;
    if (component->events.destroy != NULL)
      (component->events.destroy)(component, NULL);
    if (component->data != NULL)
      free(component->data);
  }
  vector_destroy(&entity->components);
  vector_free(&entity->children);

  list_remove_free(entity->space->entities, entity->node);
}
