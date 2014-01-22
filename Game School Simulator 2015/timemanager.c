/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "timemanager.h"
#include "schoollogic.h"
#include "../NekoEngine/input.h"


void comp_timeManager_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)self->data;
  COMPONENT *schoolLogic = entity_getComponent(self->owner, COMP_SCHOOLLOGIC);
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(self->owner, COMP_SCHOOLLOGIC);
  
  INPUT_CONTAINER *input = &self->owner->space->game->input;


  comData->timer++;

  if(comData->timer >= 6) {
    comData->months++;
    printf("\n\n\n\n\n");
    printf("Current Months: %i | Current Semester: %i | Year: %i\n\n", comData->months, comData->months/6, comData->months/12 + 1989);
    comp_schoolLogic_updateData(schoolLogic, schoolData);
    comData->timer = 0;
  }

  comData->previousYear = comData->currentYear;
  comData->currentYear = comData->months/12 + 1989;
}

void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.months = 0;
  data.previousYear = 1988;
  data.currentYear = 1989;
  data.timer = 10;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  component_depend(self, COMP_SCHOOLLOGIC);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}