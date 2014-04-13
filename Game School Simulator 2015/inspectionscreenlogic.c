/******************************************************************************
Filename: inspectionscreenlogic.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


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
    if (comData->upgradeButton) {
      LIST_NODE *node;
      LIST *buttons = list_create(); 
    
      space_getAllEntities(self->owner->space, "upgradeButton", buttons);
      node = buttons->first;
      while (node) {
        entity_destroy((ENTITY *)node->data);
        node = node->next;
      }
      list_destroy(buttons);
    }
  comData->upgradeButton = false;
  genericText_setText(comData->bonusText, " ");
  genericText_setText(comData->roomType, " ");
  genericText_setText(comData->upkeep, " ");
  genericText_setText(comData->level, " ");
  genericText_setText(comData->bonuses, " ");
  comData->clear = false;
}

void student_inspection_clear(COMPONENT *self) { 
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  genericText_setText(comData->studentName, " ");
  genericText_setText(comData->studentMajor, " ");
  genericText_setText(comData->studentGPA, " ");
  genericText_setText(comData->studentGraduation, " ");
  genericText_setText(comData->studentMotivation, " ");
  genericText_setText(comData->studentQuote, " ");
  comData->clear = false;
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

  // shut everything off if nothing is active
  if (!comData->active) {
    if (comData->clear) {
      student_inspection_clear(self);
      room_inspection_clear(self);
    }
    sprite->visible = false;
    }

  // STUDENT INSPECTION
  if (!comData->studentActive) {
    if (comData->clear)
      student_inspection_clear(self);
  }

  else if (comData->studentActive) {
    comData->clear = true;  
    comData->posActive = false;

    if (comData->active == true) {
      VEC3 position = { 0, 0, 0 };
      VEC4 color = { 0 };
      sprite->visible = true;
    
      if (comData->triggered) {
        genericText_setText(comData->studentMajor, comData->major);
        if (!comData->studentName) {
        //entity_destroy(comData->studentName);
        //comData->studentName = NULL;
          vec3_set(&position, -315, 150, 0);
          comData->studentName = genericText_create(ui, &position, NULL, "fonts/gothic/16", comData->nameBuffer, &colors[C_WHITE_LIGHT], TEXTALIGN_LEFT, TEXTALIGN_TOP);
        }
        else
          genericText_setText(comData->studentName, comData->nameBuffer);
        
        
        genericText_setText(comData->studentGPA, comData->GPA);
        genericText_setText(comData->studentGraduation, comData->expectedGraduationYear);
        genericText_setText(comData->studentMotivation, comData->motivation);
        genericText_setText(comData->studentQuote, comData->quote);
        comData->triggered = false;
      }
    }
  }
  // ROOM INSPECTION
  // Check if posX and posY are set.
  if (!comData->posActive) {
    if (comData->clear)
     room_inspection_clear(self);
  }

  else if (comData->posActive) {
    CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[comData->posY][comData->posX], COMP_ROOMLOGIC);
    comData->clear = true;
    comData->studentActive = false;

    if (comData->active == true) {
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
        genericText_setText(comData->bonusText, "Tech:\nDesign:\nArt:\n\nReputation:\nMotivation:\n\nUpkeep:");

        switch (roomData->type) {
        case (ROOMTYPE_LOBBY): 
          sprintf(comData->roomTypeBuffer, "Lobby", NULL);
          break;
        case (ROOMTYPE_CLASS): 
          sprintf(comData->roomTypeBuffer, "Class", NULL);
          break;
        case (ROOMTYPE_LIBRARY): 
          sprintf(comData->roomTypeBuffer, "Library", NULL);
          break;
        case (ROOMTYPE_TEAMSPACE): 
          sprintf(comData->roomTypeBuffer, "Teamspace", NULL);
          break;
        case (ROOMTYPE_CAFETERIA): 
          sprintf(comData->roomTypeBuffer, "Cafeteria", NULL);
          break;
        case (ROOMTYPE_STORE): 
          sprintf(comData->roomTypeBuffer, "Store", NULL);
          break;
        case (ROOMTYPE_OFFICES): 
          sprintf(comData->roomTypeBuffer, "Offices", NULL);
          break;
        case (ROOMTYPE_AUDITORIUM): 
          sprintf(comData->roomTypeBuffer, "Auditorium", NULL);
          break;
        case (ROOMTYPE_TUTORING): 
          sprintf(comData->roomTypeBuffer, "Tutor R.", NULL);
          break;
        case (ROOMTYPE_IT): 
          sprintf(comData->roomTypeBuffer, "IT Room", NULL);
          break;
        case (ROOMTYPE_RECREATION): 
          sprintf(comData->roomTypeBuffer, "Rec Room", NULL);
          break;
        case (ROOMTYPE_FIGURE): 
          sprintf(comData->roomTypeBuffer, "Figure D.", NULL);
          break;
        case (ROOMTYPE_POTTERY): 
          sprintf(comData->roomTypeBuffer, "Pottery Room (?)", NULL);
          break;
       }  

      vec3_set(&position, -265, 0, 0);
      UI_button_createUpgradeButton(self, BUTTON_ROOM_UPGRADE, &position, &colors[C_WHITE_DARK], "Upgrade!");
      genericText_setText(comData->roomType, comData->roomTypeBuffer);
      comData->upgradeButton = true;
      comData->type = roomData->type;
      comData->triggered = false;
      }
    }
  }
}
void comp_inspectionScreenLogic_initialize(COMPONENT *self, void *event) {
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  
  sprite->visible = false;
  comData->posActive = false;
  comData->studentActive = false;
  comData->upgradeButton = false;
  comData->clear = false;
}

void comp_inspectionScreenLogic(COMPONENT *self) {
  CDATA_INSPECTIONSCREEN data = { 0 };
  data.active = false;
  COMPONENT_INIT(self, COMP_INSPECTIONSCREENLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_inspectionScreenLogic_logicUpdate;
  self->events.initialize = comp_inspectionScreenLogic_initialize;
}
