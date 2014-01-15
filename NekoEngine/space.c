/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "game.h"
#include "linkedlist.h"
#include "vector.h"
#include "entity.h"
#include "util.h"

SPACE *space_create(char *name) {
  SPACE *space = (SPACE *)malloc(sizeof(SPACE));
  space->entities = list_create();
  space->systems.time.dt = 1.0f / (float)DEFAULT_FRAMERATE;
  space->systems.time.framerate = DEFAULT_FRAMERATE;
  space->systems.time.timeScale = 1.0f;
  space->systems.time.paused = false;
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

void __space_destroy(SPACE *space) {
  list_destroy(space->entities);
  list_remove_free(space->game->spaces, space->node);
}
