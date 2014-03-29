/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "weathermanager.h"
#include "sound.h"
#include "cloud.h"
#include "random.h"

void comp_weatherManager_logicUpdate(COMPONENT *self, void *event) {
  CDATA_WEATHERMANAGER *comData = (CDATA_WEATHERMANAGER *)self->data;
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  INPUT_CONTAINER *input = &self->owner->space->game->input;


  // CLOUD MANAGER
  while(comData->clouds < comData->maxClouds) {
    VEC3 pos = {0};
    vec3_set(&pos, (float)randomIntRange(-1000, 1000), (float)randomIntRange(175, 600), 0); 
    space_addEntityAtPosition(game_getSpace(self->owner->space->game, "bg"), arch_cloud, "cloud", &pos);
    ++comData->clouds;
  }
}

void comp_weatherManager(COMPONENT *self) {
  CDATA_WEATHERMANAGER data = {0};
  data.maxClouds = 20;

  COMPONENT_INIT(self, COMP_WEATHERMANGER, data);
  self->events.logicUpdate = comp_weatherManager_logicUpdate;
}