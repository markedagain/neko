/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "game.h"
#include "linkedlist.h"
#include "vector.h"
#include "entity.h"
#include "util.h"
#include "transform.h"

SPACE *space_create(char *name) {
  SPACE *space = (SPACE *)malloc(sizeof(SPACE));
  space->entities = list_create();
  space->systems.time.dt = 0;
  space->systems.time.scale = 1.0f;
  space->systems.time.currentTime = 0;
  space->systems.camera.transform.translation.x = 0.0f;
  space->systems.camera.transform.translation.y = 0.0f;
  space->systems.camera.transform.translation.z = 0.0f;
  space->systems.camera.transform.scale.x = 1.0f;
  space->systems.camera.transform.scale.y = 1.0f;
  space->systems.camera.transform.rotation = 0.0f;
  space->systems.sound.positional = false;
  space->systems.sound.volume = 1.0f;
  space->game = NULL;
  strcpy(space->name, name);
  space->active = 1;
  space->visible = 1;
  space->node = NULL;
  space->destroying = 0;
  stopwatch_start(&space->systems.time.stopwatch);
  return space;
}

ENTITY *space_addEntity(SPACE *space, void (*archetypeFunction)(ENTITY *), char *name) {
  ENTITY *entity = entity_create(archetypeFunction, name);
  int componentCount;
  entity->space = space;
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

ENTITY *space_addEntityAtPosition(SPACE *space, void (*archetypeFunction)(ENTITY *), char *name, VEC3 *position) {
  ENTITY *entity = space_addEntity(space, archetypeFunction, name);
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(entity, COMP_TRANSFORM);
  trans->translation.x = position->x;
  trans->translation.y = position->y;
  trans->translation.z = position->z;
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

void space_mouseToWorld(SPACE *space, POINT *mousePos, POINT *worldPos) {
  int x = (int)mousePos->x - (int)space->game->window.width / 2 + (int)space->systems.camera.transform.translation.x;
  int y = -((int)mousePos->y - (int)space->game->window.height / 2) + (int)space->systems.camera.transform.translation.y;
  worldPos->x = (unsigned int)x;
  worldPos->y = (unsigned int)y;
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

void space_invokeEvent(SPACE *space, EVENT_TYPE event, void *data) {
  LIST_NODE *entityNode;
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
    while (i < componentCount);
    entityNode = entityNode->next;
  }
  while (entityNode != NULL);
}

void space_tick(SPACE *space, EDATA_UPDATE *data) {
  EDATA_UPDATE logicUpdateData;
  space_invokeEvent(space, EV_FRAMEUPDATE, data);
  stopwatch_stop(&space->systems.time.stopwatch);
  space->systems.time.dt = stopwatch_delta(&space->systems.time.stopwatch);
  if (space->systems.time.scale != 0 && space->systems.time.dt >= space->game->systems.time.frameRate / space->systems.time.scale) {
    logicUpdateData.dt = space->systems.time.dt;
    logicUpdateData.elapsedTime = 0; // TODO: FIX
    space_invokeEvent(space, EV_LOGICUPDATE, &logicUpdateData);
    stopwatch_start(&space->systems.time.stopwatch);
  }
}

void __space_destroy(SPACE *space) {
  list_destroy(space->entities);
  list_remove_free(space->game->spaces, space->node);
}
