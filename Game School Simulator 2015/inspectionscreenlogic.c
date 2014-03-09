/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "inspectionscreenlogic.h"
#include "inspectionscreen.h"
#include "mousebox.h"
#include "schoollogic.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "roomactorlogic.h"

void comp_inspectionScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  SPACE *ui = game_getSpace(self->owner->space->game, "ui");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_INSPECTIONSCREEN *comData = (CDATA_INSPECTIONSCREEN *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
 
  // Check if posX and posY are set.
  if (comData->posActive) {
    CDATA_ROOMLOGIC *roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[comData->posY][comData->posX], COMP_ROOMLOGIC);

    // Is the window active?
    if (comData->active == false) {
      sprite->visible = false;
      
      if (comData->roomType) {
        entity_destroy(comData->bonuses);
        comData->bonuses = NULL;
        entity_destroy(comData->roomType);
        comData->roomType = NULL;
        entity_destroy(comData->upkeep);
        comData->upkeep = NULL;
      }
    }

    else if (comData->active == true) {
      VEC3 position = { 0, 0, 0 };
      VEC4 color = { 0, 0, 0, 1 };
      sprite->visible = true;

      if (comData->triggered) {
        roomData = (CDATA_ROOMLOGIC *)entity_getComponentData(schoolData->rooms.coord[comData->posY][comData->posX], COMP_ROOMLOGIC);
        sprintf(comData->bonusBuffer, "Tech Bonus: +%i\nDesign Bonus: +%i\nArt Bonus: +%i\nRep Bonus: +%i", roomData->techBonus, roomData->designBonus, roomData->artBonus, roomData->repBonus);
        sprintf(comData->upkeepBuffer, "Upkeep: $%li", roomData->upkeep);
        genericText_setText(comData->bonuses, comData->bonusBuffer);
        genericText_setText(comData->upkeep, comData->upkeepBuffer);
        comData->triggered = false;
      }

      if (!comData->bonuses) {
        vec3_set(&position, -318, 120, 0);
        sprintf(comData->bonusBuffer, "Tech Bonus: +%i\nDesign Bonus: +%i\nArt Bonus: +%i\nRep Bonus: +%i", roomData->techBonus, roomData->designBonus, roomData->artBonus, roomData->repBonus);
        comData->bonuses = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->bonusBuffer, &color, TEXTALIGN_LEFT, TEXTALIGN_TOP);
      }
      
      if (!comData->upkeep) {
        vec3_set(&position, -318, 70, 0);
        sprintf(comData->upkeepBuffer, "Upkeep: $%li", roomData->upkeep);
        comData->upkeep = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/12", comData->upkeepBuffer, &color, TEXTALIGN_TOP, TEXTALIGN_LEFT);  
      }

      //Check if the type of room has changed
      if (comData->type != roomData->type) {
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
          sprintf(comData->roomTypeBuffer, "Tutoring Room", NULL);
          break;
        case (ROOMTYPE_WIFI): 
          sprintf(comData->roomTypeBuffer, "Wi-Fi Room", NULL);
          break;
        case (ROOMTYPE_RECREATION): 
          sprintf(comData->roomTypeBuffer, "Rec Room", NULL);
          break;
        case (ROOMTYPE_FIGURE): 
          sprintf(comData->roomTypeBuffer, "Figure-Drawing Room", NULL);
          break;
        case (ROOMTYPE_POTTERY): 
          sprintf(comData->roomTypeBuffer, "Pottery Room (?)", NULL);
          break;
       }
      }  
      if(!comData->roomType) {
        vec3_set(&position, -318, 150, 0);
        comData->roomType = genericText_create(self->owner->space, &position, NULL, "fonts/gothic/20", comData->roomTypeBuffer, &color, TEXTALIGN_TOP, TEXTALIGN_LEFT);  
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
}

void comp_inspectionScreenLogic(COMPONENT *self) {
  CDATA_INSPECTIONSCREEN data = { 0 };
  data.active = false;
  COMPONENT_INIT(self, COMP_INSPECTIONSCREENLOGIC, data);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_inspectionScreenLogic_logicUpdate;
  self->events.initialize = comp_inspectionScreenLogic_initialize;
}
