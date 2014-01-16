/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "roomlogic.h"

void comp_roomLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)self->data;

  if(comData->type == ROOMTYPE_LOBBY) {
    printf("Im totally a lobby!!!!!!!! :O\n");
  }

  if(comData->type == ROOMTYPE_CLASS) {
    printf("GET TO CLASS\n");
  }

  if(comData->type == ROOMTYPE_LIBRARY) {
    printf("BOOKS... BOOKS EVERWHERE\n");
  }

  if(comData->type == ROOMTYPE_TEAMSPACE) {
    printf("NO FRESHMEN WELCOME...HAHA... HAHAHHAHAHAHHAH!\n");
  }

}


void comp_roomLogic(COMPONENT *self) {
  CDATA_ROOMLOGIC data;
  data.type = ROOMTYPE_LOBBY;

  COMPONENT_INIT(self, COMP_ROOMLOGIC, data);
  self->events.logicUpdate = comp_roomLogic_logicUpdate;
}