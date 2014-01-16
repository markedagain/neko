/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"
#include "room.h"
#include "roomlogic.h"
#include "../NekoEngine/linkedlist.h"

int variableTest = 1;

void comp_schoolLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  // Only display message once
  if(variableTest == 1) {
    printf("School Name: %s\n", comData->schoolName);
    variableTest = 0;
  }

  // Calculate studentCapacity
  comData->studentCapacity = comData->classrooms * 25;

  // Calculate incomingStudents
  if(comData->currentStudents < comData->studentCapacity) {
    comData->incomingStudents = 1 + comData->reputation;
    if(comData->incomingStudents > (comData->studentCapacity - comData->currentStudents)) {
      comData->incomingStudents = comData->studentCapacity - comData->currentStudents;
    }
  }
  else {
    comData->incomingStudents = 0;
  }
  //Add students
  comData->currentStudents += comData->incomingStudents;

  //Change Tuition
  if(input->keyboard.keys[KEY_LEFTBRACKET] == ISTATE_DOWN)
    comData->tuition -= 1000;
  if(input->keyboard.keys[KEY_RIGHTBRACKET] == ISTATE_DOWN)
    comData->tuition += 1000;

  //Add money
  comData->money += (comData->tuition * comData->currentStudents) / 6;
  //Lose money
  comData->money -= (comData->classrooms * 10000) / 6;

  printf("STUDENTS: %i/%i\n", comData->currentStudents, comData->studentCapacity);
  printf("MONEY: $%i\n", comData->money);
  printf("TUITION: $%i\n", comData->tuition);
  printf("REP: %i\n", comData->reputation);

  // Create Lobby room if "L" is pressed
  if(input->keyboard.keys[KEY_L] == ISTATE_RELEASED) {
    ENTITY *newRoom = space_addEntity(self->owner->space, arch_room, "Lobby");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_LOBBY;
    list_insert_end(comData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create Class room if "K" is pressed
  if(input->keyboard.keys[KEY_K] == ISTATE_RELEASED) {
    ENTITY *newRoom = space_addEntity(self->owner->space, arch_room, "Class");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_CLASS;
    list_insert_end(comData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create Library room if "J" is pressed
  if(input->keyboard.keys[KEY_J] == ISTATE_RELEASED) {
    ENTITY *newRoom = space_addEntity(self->owner->space, arch_room, "Library");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_LIBRARY;
    list_insert_end(comData->rooms, newRoom); //Add newRoom to the rooms list
  }
  // Create TeamSpace room if "H" is pressed
  if(input->keyboard.keys[KEY_H] == ISTATE_RELEASED) {
    ENTITY *newRoom = space_addEntity(self->owner->space, arch_room, "TeamSpace");
    CDATA_ROOMLOGIC *newRoomCompData = (CDATA_ROOMLOGIC *)entity_getComponentData(newRoom, COMP_ROOMLOGIC);
    newRoomCompData->type = ROOMTYPE_TEAMSPACE;
    list_insert_end(comData->rooms, newRoom); //Add newRoom to the rooms list
  }
  if(input->keyboard.keys[KEY_O] == ISTATE_RELEASED) {
    
  }
}

void comp_schoolLogic(COMPONENT *self) {
  CDATA_SCHOOLLOGIC data = { 0 };
  data.schoolName = "Tiny Game School";
  data.money = 50000;
  data.tuition = 3000;
  data.studentCapacity = 0;
  data.currentStudents = 0;
  data.incomingStudents = 0;
  data.students = list_create();
  data.classrooms = 0;
  data.rooms = list_create();
  data.reputation = 0;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}

