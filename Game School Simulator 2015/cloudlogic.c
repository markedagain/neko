/******************************************************************************
Filename: cloudlogic.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "cloudLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "weathermanager.h"
#include "random.h"
#include "timemanager.h"

// fix all mboxes to handle things
void comp_cloudLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_CLOUDLOGIC *comData = (CDATA_CLOUDLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_WEATHERMANAGER *weatherData = (CDATA_WEATHERMANAGER *)entity_getComponentData(space_getEntity(self->owner->space, "backdrop"), COMP_WEATHERMANGER);
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  ENTITY *gameManager = space_getEntity(sim, "gameManager");
  CDATA_TIMEMANAGER *timeData;

  if (gameManager) {
    timeData = (CDATA_TIMEMANAGER*)entity_getComponentData(gameManager, COMP_TIMEMANAGER);
    if (timeData->paused)
      return;
  }

  vec3_set(&trans->translation, (float)(trans->translation.x + comData->speed * 0.025f), trans->translation.y, trans->translation.z);
  if(trans->translation.x > 1000) {
    --weatherData->clouds;
    entity_destroy(self->owner);
  }
}


void comp_cloudLogic(COMPONENT *self) {
  CDATA_CLOUDLOGIC data = { 0 };
  data.speed = (float)randomIntRange(7, 14);

  COMPONENT_INIT(self, COMP_CLOUDLOGIC, data);
  self->events.logicUpdate = comp_cloudLogic_logicUpdate;
}
