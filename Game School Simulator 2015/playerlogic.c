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
#include "studentdata.h"
#include <math.h>

#define GROUND_HEIGHT 24

void comp_playerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  
}

void zoom(COMPONENT *self, float zoom) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  float newZoom = bg->systems.camera.transform.scale.x + zoom;
  float gameHeight = (float)self->owner->space->game->dimensions.height;
  newZoom = (float)max((float)min(newZoom, 1.0f), 0.5f);
    
  bg->systems.camera.transform.scale.x = newZoom;
  bg->systems.camera.transform.scale.y = newZoom;
  bg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
  mg->systems.camera.transform.scale.x = newZoom;
  mg->systems.camera.transform.scale.y = newZoom;
  mg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
  fg->systems.camera.transform.scale.x = newZoom;
  fg->systems.camera.transform.scale.y = newZoom;
  fg->systems.camera.transform.translation.y = (0.5f * ((1.0f / newZoom) * gameHeight)) - (0.5f * gameHeight) + 180 - 24;
}
void zoom_reset(COMPONENT *self) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  bg->systems.camera.transform.scale.x = 1.0f;
  bg->systems.camera.transform.scale.y = 1.0f;
  mg->systems.camera.transform.scale.x = 1.0f;
  mg->systems.camera.transform.scale.y = 1.0f;
  fg->systems.camera.transform.scale.x = 1.0f;
  fg->systems.camera.transform.scale.y = 1.0f;
}
void pan(COMPONENT *self, float x, float y) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  float zoom = bg->systems.camera.transform.scale.x;
  float newX = bg->systems.camera.transform.translation.x + x;
  float newY = bg->systems.camera.transform.translation.y + y;
  newX = (float)min(max(newX, -80.0f * 4.0f * zoom), 80.0f * 4.0f * zoom);
  bg->systems.camera.transform.translation.x = newX;
  bg->systems.camera.transform.translation.y = newY;
  mg->systems.camera.transform.translation.x = newX;
  mg->systems.camera.transform.translation.y = newY;
  fg->systems.camera.transform.translation.x = newX;
  fg->systems.camera.transform.translation.y = newY;
}
void pan_reset(COMPONENT *self) {
  SPACE *bg = game_getSpace(self->owner->space->game, "bg");
  SPACE *mg = game_getSpace(self->owner->space->game, "mg");
  SPACE *fg = game_getSpace(self->owner->space->game, "fg");
  bg->systems.camera.transform.translation.x = 0.0f;
  bg->systems.camera.transform.translation.y = 180.0f - 24.0f;
  mg->systems.camera.transform.translation.x = 0.0f;
  mg->systems.camera.transform.translation.y = 180.0f - 24.0f;
  fg->systems.camera.transform.translation.x = 0.0f;
  fg->systems.camera.transform.translation.y = 180.0f - 24.0f;
}

void comp_playerLogic_initialize(COMPONENT *self, void *event) {
  pan_reset(self);
  zoom_reset(self);
}

void comp_playerLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game,"sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData((ENTITY *)space_getEntity(simSpace, "gameManager"), COMP_SCHOOLLOGIC);

  // MANAGE INPUT
  if (input->keyboard.keys[KEY_LEFT] == ISTATE_DOWN) {
    pan(self, -4.0f, 0.0f);
  }
  if (input->keyboard.keys[KEY_RIGHT] == ISTATE_DOWN) {
    pan(self, 4.0f, 0.0f);
  }
  if (input->keyboard.keys[KEY_UP] == ISTATE_DOWN) {
    zoom(self, 0.01f);
  }
  if (input->keyboard.keys[KEY_DOWN] == ISTATE_DOWN) {
    zoom(self, -0.01f);
  }
  if (input->keyboard.keys[KEY_P] == ISTATE_DOWN) {
    zoom_reset(self);
    pan_reset(self);
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

  // List all rooms constructed
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

  // List all enrolled students
  if(input->keyboard.keys[KEY_COMMA] == ISTATE_PRESSED) {
    LIST_NODE *studentNode;
    if(schoolData->students->first != NULL) {
      studentNode = schoolData->students->first;
      do {
        ENTITY *student = (ENTITY *)studentNode->data;
        CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData(student, COMP_STUDENTDATA);
        printf("1) ");
        printf("Name: %s %s\n", studentData->name.first, studentData->name.last);
        printf("\n");
        studentNode = studentNode->next;
      } while(studentNode != NULL);
    }
  }

  // List all alumni
  if(input->keyboard.keys[KEY_M] == ISTATE_PRESSED) {
    LIST_NODE *alumniNode;
    if(schoolData->students->first != NULL) {
      alumniNode = schoolData->alumni->first;
      do {
        ENTITY *alumni = (ENTITY *)alumniNode->data;
        CDATA_STUDENTDATA *alumniData = (CDATA_STUDENTDATA *)entity_getComponentData(alumni, COMP_STUDENTDATA);
        printf("1) ");
        printf("Name: %s %s\n", alumniData->name.first, alumniData->name.last);
        printf("\n");
        alumniNode = alumniNode->next;
      } while(alumniNode != NULL);
    }
  }
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.initialize = comp_playerLogic_initialize;
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
  self->events.frameUpdate = comp_playerLogic_frameUpdate;
}
