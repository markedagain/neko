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
      //Set Values
      comData->size = 2;
      comData->repBonus = 5;
      comData->cost = 100000;
      //Modify SchoolData
      schoolData->money -= comData->cost;
      schoolData->reputation += comData->repBonus;
      break;

    case ROOMTYPE_CLASS:
      printf("New classroom created\n");
      //Set Values
      comData->size = 1;
      comData->cost = 40000;
      comData->repBonus = 1;
      comData->techBonus = 3;
      comData->designBonus = 3;
      comData->artBonus = 3;
      //Modify SchoolData
      schoolData->studentCapacity += 10;
      schoolData->money -= comData->cost;
      schoolData->reputation += comData->repBonus;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_LIBRARY:
      printf("New library created.\n");
      //Set Values
      comData->size = 2;
      comData->cost = 50000;
      comData->repBonus = 2;
      comData->techBonus = 10;
      comData->designBonus = 10;
      comData->artBonus = 10;
      //Modify SchoolData
      schoolData->money -= comData->cost;
      schoolData->reputation += comData->repBonus;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_TEAMSPACE:
      printf("New team space created\n");
      //Set Values
      comData->size = 3;
      comData->cost = 75000;
      comData->repBonus = 10;
      comData->techBonus = 5;
      comData->designBonus = 5;
      comData->artBonus = 5;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->reputation += comData->repBonus;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
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
  data.cost = 0;
  data.upkeep = 0;
  data.size = 0;
  data.techBonus = 0;
  data.designBonus = 0;
  data.artBonus = 0;
  data.motivationBonus = 0;
  data.repBonus = 0;
  data.frameCounter = 0;

  COMPONENT_INIT(self, COMP_ROOMLOGIC, data);
  self->events.logicUpdate = comp_roomLogic_logicUpdate;
}