/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"

void comp_schoolLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;



}

void comp_schoolLogic(COMPONENT *self) {
  CDATA_SCHOOLLOGIC data = { 0 };
  data.money = 0;
  data.students = list_create();

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}

