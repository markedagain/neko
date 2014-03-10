/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "timemanager.h"
#include "schoollogic.h"
#include "../NekoEngine/input.h"
#include "newsfeedlogic.h"
#include "studentmanagerlogic.h"

void comp_timeManager_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)self->data;
  COMPONENT *schoolLogic = entity_getComponent(self->owner, COMP_SCHOOLLOGIC);
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(self->owner, COMP_SCHOOLLOGIC);
  
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  if(schoolData->rooms.coord[2][7]) {
    comData->frameCounter++;

    // NEW MONTH
    if(comData->frameCounter >= self->owner->space->game->systems.time.framesPerSecond / 1) {
      SPACE *ui = game_getSpace(self->owner->space->game, "ui");
      
      comData->months++;
      
      // Monthly functions //
      comp_schoolLogic_updateDataMonth(schoolLogic, schoolData);
      comData->frameCounter = 0;
      comData->monthCounter++;
      schoolData->roomConstructed = FALSE;

      // NEW SEMESTER
      if(comData->monthCounter == 6 || comData->monthCounter == 12) {
        char message[80];
        SPACE *fg = game_getSpace(self->owner->space->game, "fg");
        ENTITY *studentManager = space_getEntity(fg, "studentManager");
        COMPONENT *studentManagerLogic = (COMPONENT *)entity_getComponent(studentManager, COMP_STUDENTMANAGERLOGIC);
        comData->currentSemester++;
        // create pop text above student's heads
        comp_studentManagerLogic_statGainText(studentManagerLogic);
        comp_schoolLogic_updateDataSemester(schoolLogic, schoolData);
        sprintf(message, pushStrings[STRINGS_SEMESTER], comData->currentSemester);
        comp_newsfeedlogic_push(self, message);
      }
    }

    // NEW YEAR
    if(comData->monthCounter >= 12) {
      char message[80];
      comData->previousYear = comData->currentYear;
      comData->currentYear++;
      comp_schoolLogic_updateDataYear(schoolLogic, schoolData);
      comData->monthCounter = 0;
      sprintf(message, pushStrings[STRINGS_YEAR], comData->currentYear);
      comp_newsfeedlogic_push(self, message);
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