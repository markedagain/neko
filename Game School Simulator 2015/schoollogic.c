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
    printf("\n\nWelcome To: %s!\n", comData->schoolName);
    variableTest = 0;
  }

  printf(">>> %hu FPS <<<\n", self->owner->space->game->systems.time.currentFramesPerSecond);
}

void comp_schoolLogic_updateData(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;
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
  newStudent = space_addEntity(self->owner->space, arch_room, "Student");
  list_insert_end(comData->students, newStudent);
  comData->currentStudents += comData->incomingStudents;

  //Add money
  comData->money += (comData->tuition * comData->currentStudents) / 6;
  //Lose money
  comData->money -= comData->roomMaintainance / 6;

  printf("STUDENTS: %i/%i\n", comData->currentStudents, comData->studentCapacity);
  printf("MONEY: $%i\n", comData->money);
  printf("TUITION: $%i\n", comData->tuition);
  printf("REP: %i\n", comData->reputation);
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
  data.roomMaintainance = 0;
  data.rooms = list_create();
  data.reputation = 0;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}