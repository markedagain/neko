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
  space->newEntities = list_create();
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
  //entity->node = list_insert_end(space->entities, (void *)entity);
  list_insert_end(space->newEntities, entity);
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
  node = space->entities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (strcmp(entity->name, name) == 0)
      return entity;
    node = node->next;
  }
  node = space->newEntities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (strcmp(entity->name, name) == 0)
      return entity;
    node = node->next;
  }
  return NULL;
}

void space_getAllEntities(SPACE *space, char *name, LIST *list) {
  LIST_NODE *node;
  node = space->entities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (strcmp(entity->name, name) == 0)
      list_insert_end(list, entity);
    node = node->next;
  }
  node = space->newEntities->first;
  while (node != NULL) {
    ENTITY *entity = (ENTITY *)node->data;
    if (strcmp(entity->name, name) == 0)
      list_insert_end(list, entity);
    node = node->next;
  }
}

void space_mouseToWorld(SPACE *space, POINT *mousePos, POINT *worldPos) {
  VEC3 camTranslate = { 0 };
  int x, y;
  float xscale = 1.0f;
  float yscale = 1.0f;
  float windowAspectRatio = (float)space->game->innerWindow.width / (float)space->game->innerWindow.height;

  space_getCamTranslate(space, &camTranslate);

  x = (int)mousePos->x - (int)(space->game->innerWindow.width / 2) + (int)camTranslate.x;
  y = -((int)mousePos->y - (int)(space->game->innerWindow.height / 2)) + (int)camTranslate.y;

  if (windowAspectRatio > space->game->dimensions.aspectRatio)
    xscale += windowAspectRatio - space->game->dimensions.aspectRatio;
  if (windowAspectRatio < space->game->dimensions.aspectRatio)
    yscale += space->game->dimensions.aspectRatio - windowAspectRatio;
  
  worldPos->x = (int)(x / ((float)space->game->innerWindow.width / (float)space->game->dimensions.width) * xscale);
  worldPos->y = (int)(y / ((float)space->game->innerWindow.height / (float)space->game->dimensions.height) * yscale);
}

void space_destroy(SPACE *space) {
  LIST_NODE *node;
  space->destroying = 1;
  list_insert_end(space->game->destroyingSpaces, space);
  node = space->newEntities->first;
  while (node) {
    ENTITY *entity = (ENTITY *)node->data;
    entity->node = list_insert_end(space->entities, entity);
    node = node->next;
  }
  list_empty(space->newEntities);
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
  while (entityNode != NULL) {
    ENTITY *entity = (ENTITY *)(entityNode->data);
    entity_invokeEvent(entity, event, data);
    entityNode = entityNode->next;
  }
  if (event == EV_DRAW) {
    entityNode = space->newEntities->first;
    while (entityNode != NULL) {
      ENTITY *entity = (ENTITY *)(entityNode->data);
      entity_invokeEvent(entity, event, data);
      entityNode = entityNode->next;
    }
  }
}

void space_invokeEventReverseways(SPACE *space, EVENT_TYPE event, void *data) {
  LIST_NODE *entityNode;
  entityNode = space->entities->last;
  while (entityNode) {
    ENTITY *entity = (ENTITY *)(entityNode->data);
    entity_invokeEvent(entity, event, data);
    entityNode = entityNode->prev;
  }
}

void space_tick(SPACE *space, EDATA_UPDATE *data) {
  EDATA_UPDATE logicUpdateData;
  LIST_NODE *node = space->newEntities->first;
  bool logicUpdated = false;
  while (node) {
    ENTITY *entity = (ENTITY *)node->data;
    entity->node = list_insert_end(space->entities, entity);
    node = node->next;
  }
  list_empty(space->newEntities);

  node = space->entities->first;
  while (node) {
    int i = 0;
    for (i = 0; i < EV_LAST; ++i)
      ((ENTITY *)node->data)->handled[i] = false;
    node = node->next;
  }

  space_invokeEventReverseways(space, EV_FRAMEUPDATE, data);
  stopwatch_stop(&space->systems.time.stopwatch);
  space->systems.time.dt = stopwatch_delta(&space->systems.time.stopwatch);
  if (space->systems.time.scale != 0 && space->systems.time.dt >= space->game->systems.time.frameRate / space->systems.time.scale) {
    logicUpdated = true;
    logicUpdateData.dt = space->systems.time.dt;
    logicUpdateData.elapsedTime = 0; // TODO: FIX
    space_invokeEventReverseways(space, EV_LOGICUPDATE, &logicUpdateData);
    stopwatch_start(&space->systems.time.stopwatch);
  }
  node = space->newEntities->first;
  while (node) {
    ENTITY *entity = (ENTITY *)node->data;
    entity_invokeEvent(entity, EV_FRAMEUPDATE, data);
    if (logicUpdated)
      entity_invokeEvent(entity, EV_LOGICUPDATE, &logicUpdateData);
    node = node->next;
  }
  
}

void __space_destroy(SPACE *space) {
  list_destroy(space->entities);
  list_destroy(space->newEntities);
  list_remove_free(space->game->spaces, space->node);
}

// gets the camera translation and modifies the input vector camTranslate
void space_getCamTranslate(SPACE *space, VEC3 *camTranslate) {
  VEC3 camScale;
  VEC3 screenScaleVec;
  float screenScale;
  MATRIX3 transform = { 0 };

  camScale.x = space->systems.camera.transform.scale.x;
  camScale.y = space->systems.camera.transform.scale.y;

  screenScale = (float)space->game->innerWindow.width / space->game->dimensions.width;
  screenScaleVec.x = screenScale;
  screenScaleVec.y = screenScale;

  matrix3_identity(&transform);
  matrix3_scale(&transform, &camScale);
  matrix3_scale(&transform, &screenScaleVec);

  camTranslate->x = space->systems.camera.transform.translation.x;
  camTranslate->y = space->systems.camera.transform.translation.y;

  matrix3_apply_to_vector(camTranslate, &transform);
}