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

  if(schoolData->rooms.coord[2][7]) {
    comData->frameCounter++;

    // New month every x frames (1 FPS)
    if(comData->frameCounter >= self->owner->space->game->systems.time.framesPerSecond / 1) {
      comData->months++;
      printf("\n\n\n\n\n\n");
      printf("Month: %i  Semester: %i  Year: %i\n\n", comData->months, comData->currentSemester, comData->currentYear);
      comp_schoolLogic_updateDataMonth(schoolLogic, schoolData);
      comData->frameCounter = 0;
      comData->monthCounter++;
      schoolData->roomConstructed = FALSE;

      if(comData->monthCounter == 6 || comData->monthCounter == 12) {
        comData->currentSemester++;
        comp_schoolLogic_updateDataSemester(schoolLogic, schoolData);
      }
    }

    if(comData->monthCounter >= 12) {
      comData->previousYear = comData->currentYear;
      comData->currentYear++;
      comp_schoolLogic_updateDataYear(schoolLogic, schoolData);
      comData->monthCounter = 0;
    }
  }
}

void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.months = 0;
  data.currentSemester = 0;
  data.previousYear = 1988;
  data.currentYear = 1989;
  data.frameCounter = 10;
  data.monthCounter = 0;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  component_depend(self, COMP_SCHOOLLOGIC);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}