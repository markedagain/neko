/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"
#include "room.h"
#include "roomlogic.h"
#include "student.h"
#include "../NekoEngine/linkedlist.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"

int variableTest = 1;

void comp_schoolLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  INPUT_CONTAINER *input = &self->owner->space->game->input;

  // Only display message once
  if(variableTest == 1) {
    //CDATA_SPRITE *sprite;
    //sprite = (CDATA_SPRITE *)entity_connect(self->owner, comp_sprite);
    //sprite->source = "dev64";
    printf("\n\n\n\n\n\n\n\n\n\n\n\nWelcome To %s!\n\n\n\n\n\n\n\n\n", comData->schoolName);
    variableTest = 0;
  }

  //printf(">>> %hu FPS <<<\n", self->owner->space->game->systems.time.currentFramesPerSecond);
}

void comp_schoolLogic_updateData(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;
  int i = 0;
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
  if(comData->incomingStudents > 0) {
    for(i = 0; i <= comData->incomingStudents; i++)
    {
      newStudent = space_addEntity(self->owner->space, arch_student, "Student");
      list_insert_end(comData->students, newStudent);
      comData->currentStudents++;
    }
  }

  //Add money
  comData->money += (comData->tuition * comData->currentStudents) / 6.0;
  //Lose money
  comData->money -= (float)comData->roomMaintainance / 6.0;

  printf("STUDENTS: %i/%i\n", comData->currentStudents, comData->studentCapacity);
  printf("MONEY: $%i\n", comData->money);
  printf("TUITION: $%i\n", comData->tuition);
  printf("REP: %i\n", comData->reputation);
}

void comp_schoolLogic_destroy(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  list_destroy(comData->rooms);
  list_destroy(comData->students);
}

void comp_schoolLogic(COMPONENT *self) {
  CDATA_SCHOOLLOGIC data = { 0 };
  data.schoolName = "Eduardo's Super Awesome Game School";
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