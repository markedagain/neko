/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "timemanager.h"
#include "schoollogic.h"
#include "../NekoEngine/input.h"


void comp_timeManager_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)self->data;
  CDATA_SCHOOLLOGIC *schoolData;
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  

  schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(self->owner, COMP_SCHOOLLOGIC);

  comData->months++;

  printf("Current Months: %i | Current Semester: %i | Year: %i\n\n\n", comData->months, comData->months/6, comData->months/12 + 1989);

  if((comData->currentYear > comData->previousYear)
      || (input->keyboard.keys[KEY_B] == ISTATE_DOWN)) {
    schoolData->classrooms++;
    schoolData->money -= 100000;
  }

  comData->previousYear = comData->currentYear;
  comData->currentYear = comData->months/12 + 1989;
}

void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.months = 0;
  data.previousYear = 1989;
  data.currentYear = 1989;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  component_depend(self, COMP_SCHOOLLOGIC);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}