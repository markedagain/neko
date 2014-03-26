/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "roomlogic.h"
#include "schoollogic.h"
#include "inspectionscreenlogic.h"

void comp_roomLogic_frameUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)self->data;
  
  // INITIALIZE
  if(comData->frameCounter == 0) {
    comp_roomLogic_createRoom(self);
  }

  comData->frameCounter++;
}

void comp_roomLogic_logicUpdate(COMPONENT *self, void *event) {
  
}

void comp_roomLogic_createRoom(COMPONENT *self) {
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)self->data;
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *) entity_getComponentData((ENTITY *)space_getEntity(self->owner->space, "gameManager"), COMP_SCHOOLLOGIC);

  // UPKKEP CALCULATED PER MONTH
  switch (comData->type) {
    case ROOMTYPE_LOBBY:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_LOBBY);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_LOBBY);
      //Modify SchoolData
      schoolData->money -= comData->cost;
      break;

    case ROOMTYPE_CLASS:
      //Set Values
      comData->size = 1;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_CLASS);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_CLASS);
      comData->techBonus = 1;
      comData->designBonus = 1;
      comData->artBonus = 1;
      comData->upkeep = 10000;
      //Modify SchoolData
      schoolData->studentCapacity += 30;
      schoolData->money -= comData->cost;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_LIBRARY:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_LIBRARY);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_LIBRARY);
      comData->techBonus = 2;
      comData->designBonus = 2;
      comData->artBonus = 2;
      comData->upkeep = 15000;
      //Modify SchoolData
      schoolData->money -= comData->cost;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_TEAMSPACE:
      //Set Values
      comData->size = 3;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_TEAMSPACE);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_TEAMSPACE);
      comData->motivationBonus = 5;
      comData->upkeep = 20000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->motivationBonus += comData->motivationBonus;
      break;

    case ROOMTYPE_CAFETERIA:
      //Set Values
      comData->size = 3;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_CAFETERIA);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_CAFETERIA);
      comData->motivationBonus = 3;
      comData->upkeep = -2000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->motivationBonus += comData->motivationBonus;
      break;

    case ROOMTYPE_STORE:
      //Set Values
      comData->size = 1;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_STORE);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_STORE);
      comData->upkeep = -5000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      break;
    
    case ROOMTYPE_OFFICES:
      //Set Values
      comData->size = 1;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_OFFICES);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_OFFICES);
      comData->techBonus = 2;
      comData->designBonus = 2;
      comData->artBonus = 2;
      comData->upkeep = 10000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_AUDITORIUM:
      //Set Values (Also unlocks special events)
      comData->size = 3;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_AUDITORIUM);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_AUDITORIUM);
      comData->motivationBonus = 5;
      comData->upkeep = 24000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->motivationBonus += comData->motivationBonus;
      break;

    case ROOMTYPE_TUTORING:
      //Set Values
      comData->size = 1;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_TUTORING);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_TUTORING);
      comData->techBonus = 1;
      comData->designBonus = 1;
      comData->artBonus = 1;
      comData->motivationBonus = 1;
      comData->upkeep = 5000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->techBonus += comData->techBonus;
      schoolData->designBonus += comData->designBonus;
      schoolData->artBonus += comData->artBonus;
      schoolData->motivationBonus += comData->motivationBonus;
      break;

    case ROOMTYPE_WIFI:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_WIFI);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_WIFI);
      comData->techBonus = 5;
      comData->upkeep = 15000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->techBonus += comData->techBonus;
      break;

    case ROOMTYPE_RECREATION:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_RECREATION);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_RECREATION);
      comData->designBonus = 5;
      comData->upkeep = 15000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->designBonus += comData->designBonus;
      break;

    case ROOMTYPE_FIGURE:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_FIGURE);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_FIGURE);
      comData->artBonus = 5;
      comData->upkeep = 15000;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      schoolData->artBonus += comData->artBonus;
      break;

    case ROOMTYPE_POTTERY:
      //Set Values
      comData->size = 2;
      comData->cost = comp_roomLogic_getRoomCost(ROOMTYPE_POTTERY);
      comData->upgradeCost = comp_roomLogic_getRoomUpgradeCost(ROOMTYPE_POTTERY);
      comData->upkeep = 20;
      //Modify SchoolLogic
      schoolData->money -= comData->cost;
      break;

    default:
      printf("ERROR: Unkown room created!!\n");
      break;
    }
}

void comp_roomLogic_upgradeRoom(COMPONENT *self) {
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  ENTITY *inspectionScreen = space_getEntity(ui, "inspection_screen");
  CDATA_INSPECTIONSCREEN *inspectData = (CDATA_INSPECTIONSCREEN *)entity_getComponentData(space_getEntity(ui, "inspection_screen"), COMP_INSPECTIONSCREENLOGIC); 
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_ROOMLOGIC *comData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[inspectData->posY][inspectData->posX], COMP_ROOMLOGIC);

  switch (comData->type) {
    case ROOMTYPE_LOBBY:
      break;

    case ROOMTYPE_CLASS:
      //Set Values
      comData->upkeep += 3000;
      ++comData->level;
      //Modify SchoolData
      schoolData->studentCapacity += 10;
      schoolData->money -= comData->upgradeCost;
      break;

    case ROOMTYPE_LIBRARY:
      //Set Values
      comData->techBonus += 1;
      comData->designBonus = 1;
      comData->artBonus += 1;
      comData->upkeep += 7500;
      ++comData->level;
      //Modify SchoolData
      schoolData->money -= comData->upgradeCost;
      schoolData->techBonus += 1;
      schoolData->designBonus += 1;
      schoolData->artBonus += 1;
      break;

    case ROOMTYPE_TEAMSPACE:
      //Set Values
      comData->upkeep += 10000;
      comData->motivationBonus += 2;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->motivationBonus += 2;
      break;

    case ROOMTYPE_CAFETERIA:
      //Set Values
      comData->motivationBonus += 1;
      comData->upkeep -= 1000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->motivationBonus += 1;
      break;

    case ROOMTYPE_STORE:
      //Set Values
      comData->upkeep -= 1000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      break;
    
    case ROOMTYPE_OFFICES:
      //Set Values
      comData->techBonus += 1;
      comData->designBonus += 1;
      comData->artBonus += 1;
      comData->upkeep += 5000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->techBonus += 1;
      schoolData->designBonus += 1;
      schoolData->artBonus += 1;
      break;

    case ROOMTYPE_AUDITORIUM:
      //Set Values
      comData->motivationBonus += 2;
      comData->upkeep += 12000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->motivationBonus += 2;
      break;

    case ROOMTYPE_TUTORING:
      //Set Values
      comData->techBonus += 1;
      comData->designBonus += 1;
      comData->artBonus += 1;
      comData->motivationBonus += 2;
      comData->upkeep += 5000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->techBonus += 1;
      schoolData->designBonus += 1;
      schoolData->artBonus += 1;
      schoolData->motivationBonus += 2;
      break;

    case ROOMTYPE_WIFI:
      //Set Values
      comData->techBonus += 3;
      comData->upkeep += 10000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->techBonus += 3;
      break;

    case ROOMTYPE_RECREATION:
      //Set Values
      comData->designBonus += 3;
      comData->motivationBonus += 2;
      comData->upkeep += 10000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->designBonus += 3;
      schoolData->motivationBonus += 2;
      break;

    case ROOMTYPE_FIGURE:
      //Set Values
      comData->artBonus += 3;
      comData->motivationBonus += 2;
      comData->upkeep += 10000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      schoolData->artBonus += 3;
      schoolData->motivationBonus += 2;
      break;

    case ROOMTYPE_POTTERY:
      //Set Values
      comData->upkeep += 20000;
      ++comData->level;
      //Modify SchoolLogic
      schoolData->money -= comData->upgradeCost;
      break;

    default:
      printf("ERROR: Unkown room created!!\n");
      break;
    }
}


void comp_roomLogic(COMPONENT *self) {
  CDATA_ROOMLOGIC data;
  data.cost = 0;
  data.upkeep = 0;
  data.size = 0;
  data.level = 1;
  data.techBonus = 0;
  data.designBonus = 0;
  data.artBonus = 0;
  data.motivationBonus = 0;
  data.repBonus = 0;
  data.frameCounter = 0;

  COMPONENT_INIT(self, COMP_ROOMLOGIC, data);
  self->events.logicUpdate = comp_roomLogic_logicUpdate;
  self->events.frameUpdate = comp_roomLogic_frameUpdate;
}

int comp_roomLogic_getRoomCost(ROOM_TYPE type) {
    switch (type) {
    case ROOMTYPE_LOBBY:
      return 250000;

    case ROOMTYPE_CLASS:
      return 100000;

    case ROOMTYPE_LIBRARY:
      return 200000;

    case ROOMTYPE_TEAMSPACE:
      return 300000;

    case ROOMTYPE_CAFETERIA:
      return 350000;

    case ROOMTYPE_STORE:
      return 250000;
    
    case ROOMTYPE_OFFICES:
      return 100000;

    case ROOMTYPE_AUDITORIUM:
      return 500000;

    case ROOMTYPE_TUTORING:
      return 80000;

    case ROOMTYPE_WIFI:
      return 150000;

    case ROOMTYPE_RECREATION:
      return 150000;

    case ROOMTYPE_FIGURE:
      return 150000;

    case ROOMTYPE_POTTERY:
      return 1000000;

    default:
      return 0;
  }
}

int comp_roomLogic_getRoomUpgradeCost(ROOM_TYPE type) {
    switch (type) {
    case ROOMTYPE_LOBBY:
      return 0;

    case ROOMTYPE_CLASS:
      return 5000;

    case ROOMTYPE_LIBRARY:
      return 10000;

    case ROOMTYPE_TEAMSPACE:
      return 30000;

    case ROOMTYPE_CAFETERIA:
      return 5000;

    case ROOMTYPE_STORE:
      return 5000;
    
    case ROOMTYPE_OFFICES:
      return 5000;

    case ROOMTYPE_AUDITORIUM:
      return 5000;

    case ROOMTYPE_TUTORING:
      return 5000;

    case ROOMTYPE_WIFI:
      return 5000;

    case ROOMTYPE_RECREATION:
      return 5000;

    case ROOMTYPE_FIGURE:
      return 5000;

    case ROOMTYPE_POTTERY:
      return 5000;

    default:
      return 0;
  }
}
