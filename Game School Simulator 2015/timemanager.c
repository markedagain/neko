/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "timemanager.h"

void comp_timeManager_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TIMEMANAGER *comData = (CDATA_TIMEMANAGER *)self->data;

  comData->months++;
  printf("Current Months: %i", comData->months);

}

void comp_timeManager(COMPONENT *self) {
  CDATA_TIMEMANAGER data = { 0 };
  data.months = 0;

  COMPONENT_INIT(self, COMP_TIMEMANAGER, data);
  self->events.logicUpdate = comp_timeManager_logicUpdate;
}