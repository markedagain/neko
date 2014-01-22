/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "roomlogic.h"
#include "schoollogic.h"

void comp_roomLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)self->data;
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_SCHOOLLOGIC);
  
  // INITIALIZE
  if(comData->frameCounter == 0) {
    switch (comData->type) {
    case ROOMTYPE_LOBBY:
      printf("New lobby created\n");
      schoolData->roomMaintainance += 10000;
      break;

    case ROOMTYPE_CLASS:
      printf("New classroom created\n");
      schoolData->roomMaintainance += 20000;
      schoolData->studentCapacity += 25;
      break;

    case ROOMTYPE_LIBRARY:
      printf("New library created.\n");
      schoolData->roomMaintainance += 25000;
      break;

    case ROOMTYPE_TEAMSPACE:
      printf("New team space created\n");
      schoolData->roomMaintainance += 30000;
      break;

    default:
      printf("ERROR: Unkown room created!!\n");
      break;
    }
  }

  comData->frameCounter++;
}


void comp_roomLogic(COMPONENT *self) {
  CDATA_ROOMLOGIC data;
  data.type = ROOMTYPE_LOBBY;
  data.upkeep = 0;
  data.frameCounter = 0;

  COMPONENT_INIT(self, COMP_ROOMLOGIC, data);
  self->events.logicUpdate = comp_roomLogic_logicUpdate;
}