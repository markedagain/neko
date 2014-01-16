/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "roomlogic.h"

void comp_roomLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)self->data;

  switch (comData->type) {
  case ROOMTYPE_LOBBY:
    printf("Im totally a lobby!!!!!!!! :O\n");
    break;

  case ROOMTYPE_CLASS:
    printf("GET TO CLASS\n");
    break;

  case ROOMTYPE_LIBRARY:
    printf("BOOKS...BOOKS EVERWHERE.\n");
    break;

  case ROOMTYPE_TEAMSPACE:
    printf("NO FRESHMEN WELCOME...HAHA... HAHAHHAHAHAHHAH!\n");
    break;

  default:
    printf("Im totally a lobby!!!!!!!! :O\n");
    break;
  }
}


void comp_roomLogic(COMPONENT *self) {
  CDATA_ROOMLOGIC data;
  data.type = ROOMTYPE_LOBBY;
  data.upkeep = 0;

  COMPONENT_INIT(self, COMP_ROOMLOGIC, data);
  self->events.logicUpdate = comp_roomLogic_logicUpdate;
}