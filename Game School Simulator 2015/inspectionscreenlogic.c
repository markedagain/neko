/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "inspectionscreenlogic.h"
#include "inspectionscreen.h"
#include "mousebox.h"
#include "schoollogic.h"
#include "UI_button.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "roomactorlogic.h"
#include "studentactorlogic.h"
#include "colors.h"

void room_inspection_clear(COMPONENT *self) {
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  
  if (comData->roomType) {
    LIST_NODE *node;
    LIST *buttons = list_create(); 
  
    space_getAllEntities(self->owner->space, "upgradeButton", buttons);
    node = buttons->first;
    while (node) {
    entity_destroy((ENTITY *)node->data);
    node = node->next;
    }

  list_destroy(buttons);
    entity_destroy(comData->bonuses);
    comData->bonuses = NULL;
    entity_destroy(comData->roomType);
    comData->roomType = NULL;
    entity_destroy(comData->upkeep);
    comData->upkeep = NULL;
    entity_destroy(comData->level);
    comData->level = NULL;
    entity_destroy(comData->bonusText);
    comData->bonusText = NULL;
  }
}

void student_inspection_clear(COMPONENT *self) {
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data; 
  
  if (comData->studentName) {
   entity_destroy(comData->studentName);
   comData->studentName = NULL;
   entity_destroy(comData->studentMajor);
   comData->studentMajor = NULL;
   entity_destroy(comData->studentGPA);
   comData->studentGPA = NULL;
   entity_destroy(comData->studentGraduation);
   comData->studentGraduation = NULL;
   entity_destroy(comData->studentMotivation);
   comData->studentMotivation = NULL;
   }
}

void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  CDATA_SCHOOLLOGIC *studentData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);

  // STUDENT INSPECTION
  if (!comData->studentActive)
    student_inspection_clear(self);

  if (comData->studentActive) {
      comData->posActive = false;

    // Is the window active?
    if (comData->active == false) {
      student_inspection_clear(self);
      sprite->visible = false;
    }

    else if (comData->active == true) {
      VEC3 position = { 0, 0, 0 };
      VEC4 color = { 0 };
      sprite->visible = true;

      if (!comData->studentName) {
        vec3_set(&position, -315, 150, 0);
        comData->studentName = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/16", comData->nameBuffer, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
        vec3_set(&position, -315, 110, 0);
        comData->studentMajor = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/16", comData->major, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
        vec3_set(&position, -315, 90, 0);
        comData->studentGPA = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->GPA, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
        vec3_set(&position, -315, 70, 0);
        comData->studentMotivation = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->motivation, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
        vec3_set(&position, -315, 50, 0);
        comData->studentGraduation = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->expectedGraduationYear, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
      }
      
      if (comData->triggered) {
        genericText_setText(comData->studentName, comData->nameBuffer);
        genericText_setText(comData->studentMajor, comData->major);
        genericText_setText(comData->studentGPA, comData->GPA);
        genericText_setText(comData->studentGraduation, comData->expectedGraduationYear);
        genericText_setText(comData->studentMotivation, comData->motivation);
        comData->triggered = false;
      }

    }
  }
  // ROOM INSPECTION
  // Check if posX and posY are set.
  if (!comData->posActive)
    room_inspection_clear(self);

  if (comData->posActive) {
    CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[comData->posY][comData->posX], COMP_ROOMLOGIC);

    // Is the window active?
    if (comData->active == false) {
      student_inspection_clear(self);
      room_inspection_clear(self);
      sprite->visible = false;
    }

    else if (comData->active == true) {
      VEC3 position = { 0, 0, 0 };
      VEC4 color = { 0 };
      sprite->visible = true;

      if (comData->triggered) {
        roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[comData->posY][comData->posX], COMP_ROOMLOGIC);
        sprintf(comData->bonusBuffer, "+%i\n+%i\n+%i\n\n+%i\n+%i", roomData->techBonus, roomData->designBonus, roomData->artBonus, roomData->repBonus, roomData->motivationBonus);
        sprintf(comData->upkeepBuffer, "$%li", roomData->upkeep);
        sprintf(comData->levelBuffer, "Level %i", roomData->level);
        genericText_setText(comData->bonuses, comData->bonusBuffer);
        genericText_setText(comData->upkeep, comData->upkeepBuffer);
        genericText_setText(comData->level, comData->levelBuffer);
        comData->triggered = false;
      }

      if (!comData->bonusText) {
        vec3_set(&position, -315, 110, 0);
        comData->bonusText = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", "Tech:\nDesign:\nArt:\n\nReputation:\nMotivation:\n\nUpkeep:", &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
      }

      if (!comData->bonuses) {
        vec3_set(&position, -215, 110, 0);
        sprintf(comData->bonusBuffer, "+%i\n+%i\n+%i\n\n+%i\n+%i", roomData->techBonus, roomData->designBonus, roomData->artBonus, roomData->repBonus, roomData->motivationBonus);
        comData->bonuses = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->bonusBuffer, &colors[C_WHITE_LIGHT], TEXTALIGN_RIGHT, TEXTALIGN_TOP);
      }
      
      if (!comData->upkeep) {
        vec3_set(&position, -215, 26, 0);
        sprintf(comData->upkeepBuffer, "$%li", roomData->upkeep);
        comData->upkeep = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->upkeepBuffer, &colors[C_RED_LIGHT], TEXTALIGN_RIGHT, TEXTALIGN_TOP);  
      }

      if (!comData->level) {
        vec3_set(&position, -315, 130, 0);
        sprintf(comData->levelBuffer, "Level %i", roomData->level);
        comData->level = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->levelBuffer, &colors[C_WHITE_LIGHT], TEXTALIGN_TOP, TEXTALIGN_LEFT);  
      }
        //Check if the type of room has changed
      if (comData->type != roomData->type) {
        sprintf(comData->bonusBuffer, "+%i\n+%i\n+%i\n\n+%i\n+%i", roomData->techBonus, roomData->designBonus, roomData->artBonus, roomData->repBonus, roomData->motivationBonus);
        sprintf(comData->upkeepBuffer, "$%li", roomData->upkeep);
        sprintf(comData->levelBuffer, "Level %i", roomData->level);
        genericText_setText(comData->bonuses, comData->bonusBuffer);
        genericText_setText(comData->upkeep, comData->upkeepBuffer);
        genericText_setText(comData->level, comData->levelBuffer);
        
        switch (roomData->type) {
        case (ROOMTYPE_LOBBY): 
          sprintf(comData->roomTypeBuffer, "Lobby", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_CLASS): 
          sprintf(comData->roomTypeBuffer, "Class", NULL);
          sprintf(comData->upgradeMessageBuffer, "Improve Desks!", NULL);
          break;
        case (ROOMTYPE_LIBRARY): 
          sprintf(comData->roomTypeBuffer, "Library", NULL);
          sprintf(comData->upgradeMessageBuffer, "Purchase Books!", NULL);
          break;
        case (ROOMTYPE_TEAMSPACE): 
          sprintf(comData->roomTypeBuffer, "Teamspace", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_CAFETERIA): 
          sprintf(comData->roomTypeBuffer, "Cafeteria", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_STORE): 
          sprintf(comData->roomTypeBuffer, "Store", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_OFFICES): 
          sprintf(comData->roomTypeBuffer, "Offices", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_AUDITORIUM): 
          sprintf(comData->roomTypeBuffer, "Auditorium", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_TUTORING): 
          sprintf(comData->roomTypeBuffer, "Tutoring Room", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_IT): 
          sprintf(comData->roomTypeBuffer, "IT Room", NULL);
          sprintf(comData->upgradeMessageBuffer, "Improve IT!", NULL);
          break;
        case (ROOMTYPE_RECREATION): 
          sprintf(comData->roomTypeBuffer, "Rec Room", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_FIGURE): 
          sprintf(comData->roomTypeBuffer, "Figure-Drawing Room", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
        case (ROOMTYPE_POTTERY): 
          sprintf(comData->roomTypeBuffer, "Pottery Room (?)", NULL);
          sprintf(comData->upgradeMessageBuffer, "Upgrade!", NULL);
          break;
       }
      }  
      if(!comData->roomType) {
        vec3_set(&position, -315, 150, 0);
        comData->roomType = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", comData->roomTypeBuffer, &colors[C_WHITE_LIGHT], TEXTALIGN_TOP, TEXTALIGN_LEFT);  
        vec3_set(&position, -265, 0, 0);
        UI_button_createUpgradeButton(self, BUTTON_ROOM_UPGRADE, &position, &colors[C_WHITE_DARK], "Upgrade!");
      }
      genericText_setText(comData->roomType, comData->roomTypeBuffer);
      comData->type = roomData->type;
    }
  }
}

void comp_inspectionScreenLogic_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  
  sprite->visible = false;
  comData->posActive = false;
  comData->studentActive = false;
}

void comp_inspectionScreenLogic(COMPONENT *self) {
  CDATA_INSPECTIONSCREEN data = { 0 };
  data.active = false;
  COMPONENT_INIT(self, COMP_INSPECTIONSCREENLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_inspectionScreenLogic_logicUpdate;
  self->events.initialize = comp_inspectionScreenLogic_initialize;
}
