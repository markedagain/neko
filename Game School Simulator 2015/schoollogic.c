/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"

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
    comData->incomingStudents = 3 + comData->reputation;
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
  comData->money += comData->tuition * comData->currentStudents;

  printf("STUDENTS: %i/%i\n", comData->currentStudents, comData->studentCapacity);
  printf("MONEY: $%i\n", comData->money);
  printf("TUITION: $%i\n", comData->tuition);
  printf("REP: %i\n", comData->reputation);
}

void comp_schoolLogic(COMPONENT *self) {
  CDATA_SCHOOLLOGIC data = { 0 };
  data.schoolName = "Tiny Game School";
  data.money = 0;
  data.tuition = 1000;
  data.studentCapacity = 0;
  data.currentStudents = 0;
  data.incomingStudents = 0;
  data.students = list_create();
  data.classrooms = 1;
  data.reputation = 0;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}

