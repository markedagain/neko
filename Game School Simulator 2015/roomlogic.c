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
      schoolData->money -= 100000;
      schoolData->reputation += 5;
      break;

    case ROOMTYPE_CLASS:
      printf("New classroom created\n");
      schoolData->roomMaintainance += 20000;
      schoolData->studentCapacity += 10;
      schoolData->money -= 40000;
      schoolData->reputation += 1;
      schoolData->techBonus += 3;
      schoolData->designBonus += 3;
      schoolData->artBonus += 3;
      break;

    case ROOMTYPE_LIBRARY:
      printf("New library created.\n");
      schoolData->roomMaintainance += 25000;
      schoolData->money -= 50000;
      schoolData->reputation += 2;
      schoolData->techBonus += 10;
      schoolData->designBonus += 10;
      schoolData->artBonus += 10;
      break;

    case ROOMTYPE_TEAMSPACE:
      printf("New team space created\n");
      schoolData->roomMaintainance += 50000;
      schoolData->money -= 75000;
      schoolData->reputation += 10;
      schoolData->techBonus += 5;
      schoolData->designBonus += 5;
      schoolData->artBonus += 5;
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