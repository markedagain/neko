/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "playerLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/game.h"
#include "room.h"
#include "roomlogic.h"
#include "schoollogic.h"
#include "gamemanager.h"

void comp_playerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  ENTITY *simSpace = game_getSpace(self->owner->space->game,"simulation");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);

  if (input->keyboard.keys[KEY_SPACE]) {
    trans->scale.x *= 1.01f;
    trans->scale.y *= 1.01f;
    trans->rotation += 0.01f;
  }
  if (input->keyboard.keys[KEY_LEFT] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.x -= 4.0f;
  }
  if (input->keyboard.keys[KEY_RIGHT] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.x += 4.0f;
  }
  if (input->keyboard.keys[KEY_UP] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.y += 4.0f;
  }
  if (input->keyboard.keys[KEY_DOWN] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.translation.y -= 4.0f;
  }
  if (input->keyboard.keys[KEY_A] == ISTATE_PRESSED) {
    trans->translation.x -= 4.0f;
  }
  if (input->keyboard.keys[KEY_D] == ISTATE_PRESSED) {
    trans->translation.x += 4.0f;
  }
  if (input->keyboard.keys[KEY_W] == ISTATE_PRESSED) {
    trans->translation.y += 4.0f;
  }
  if (input->keyboard.keys[KEY_S] == ISTATE_PRESSED) {
    trans->translation.y -= 4.0f;
  }
  if (input->keyboard.keys[KEY_O] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.scale.x += 0.1f;
    self->owner->space->systems.camera.transform.scale.y += 0.1f;
  }
  if (input->keyboard.keys[KEY_P] == ISTATE_DOWN) {
    self->owner->space->systems.camera.transform.scale.x -= 0.1f;
    self->owner->space->systems.camera.transform.scale.y -= 0.1f;
  }

  //Change Tuition
  if(input->keyboard.keys[KEY_LEFTBRACKET] == ISTATE_PRESSED)
    schoolData->tuition -= 1000;
  if(input->keyboard.keys[KEY_RIGHTBRACKET] == ISTATE_PRESSED)
    schoolData->tuition += 1000;

  //Create Lobby room if "L" is pressed
  if(input->keyboard.keys[KEY_L] == ISTATE_PRESSED) {
    ENTITY *newRoom = space_addEntity(simSpace, arch_room, "Lobby");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_LOBBY;
    list_insert_end(schoolData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create Class room if "K" is pressed
  if(input->keyboard.keys[KEY_K] == ISTATE_PRESSED) {
    ENTITY *newRoom = space_addEntity(simSpace, arch_room, "Class");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_CLASS;
    list_insert_end(schoolData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create Library room if "J" is pressed
  if(input->keyboard.keys[KEY_J] == ISTATE_PRESSED) {
    ENTITY *newRoom = space_addEntity(simSpace, arch_room, "Library");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_LIBRARY;
    list_insert_end(schoolData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create TeamSpace room if "H" is pressed
  if(input->keyboard.keys[KEY_H] == ISTATE_PRESSED) {
    ENTITY *newRoom = space_addEntity(simSpace, arch_room, "TeamSpace");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_TEAMSPACE;
    list_insert_end(schoolData->rooms, newRoom); //Add newRoom to the rooms list
  }

  if(input->keyboard.keys[KEY_PERIOD] == ISTATE_PRESSED) {
    LIST_NODE *roomNode;
    if(schoolData->rooms->first != NULL) {
      roomNode = schoolData->rooms->first;
      do {
        ENTITY *room = (ENTITY *)roomNode->data;
        printf("1) ");
        printf(room->name);
        printf("\n");
        roomNode = roomNode->next;
      } while(roomNode != NULL);
    }
  }
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
}
