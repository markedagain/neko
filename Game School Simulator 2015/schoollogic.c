/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "schoollogic.h"
#include "room.h"
#include "roomlogic.h"
#include "student.h"
#include "studentdata.h"
#include "../NekoEngine/linkedlist.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include <math.h>

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

void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  int i = 0;
  LIST_NODE *studentPtr;
  
  // Calculate incomingStudents
  if(comData->currentStudents < comData->studentCapacity) {
    comData->incomingStudents += 1 + comData->reputation;
    if(comData->incomingStudents > (comData->studentCapacity - comData->currentStudents)) {
      comData->incomingStudents = comData->studentCapacity - comData->currentStudents;
    }
  }
  else {
    comData->incomingStudents = 0;
  }

  //Add money
  comData->money += (int)floor((float)(comData->tuition * comData->currentStudents) / 6.0f);
  //Lose money
  comData->money -= (int)floor((float)comData->roomMaintainance / 6.0f);

  // Add student stats
  studentPtr = comData->students->first;
  for(i = 0; i < comData->students->count; i++) {
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
    studentData->techSkill += (int)(1 + comData->techBonus * ((float)studentData->motivation / 100.0));
    studentData->designSkill += (int)(1 + comData->designBonus * ((float)studentData->motivation / 100.0));
    studentData->artSkill += (int)(1 + comData->artBonus * ((float)studentData->motivation / 100.0));
    studentPtr = studentPtr->next;
  }

  printf("Students: %i/%i", comData->currentStudents, comData->studentCapacity);
  printf("       Incoming: %i\n", comData->incomingStudents);
  printf("Money: $%i", comData->money);
  printf("       Tuition: $%i\n", comData->tuition);
  printf("Rep: %i", comData->reputation);
  printf("              Alumni: %i\n", comData->alumni->count);
}

void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  ENTITY *newStudent;

  int i = 0;

  //Add students
  if(comData->incomingStudents > 0) {
    for(i = 0; i <= comData->incomingStudents; i++)
    {
      CDATA_STUDENTDATA *studentData;
      LIST_NODE *nodeptr;
      newStudent = space_addEntity(self->owner->space, arch_student, "Student");
      studentData = (CDATA_STUDENTDATA *)entity_getComponentData(newStudent, COMP_STUDENTDATA);
      nodeptr = list_insert_end(comData->students, newStudent);
      studentData->listNodePtr = nodeptr;
      comData->currentStudents++;
    }
    comData->incomingStudents = 0;
  }
}

void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData) {
  
}

void comp_schoolLogic_destroy(COMPONENT *self, void *event) {
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)self->data;
  list_destroy(comData->rooms);
  list_destroy(comData->students);
  list_destroy(comData->alumni);
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
  data.alumni = list_create();
  data.roomMaintainance = 0;
  data.rooms = list_create();
  data.reputation = 0;
  data.techBonus = 1;
  data.designBonus = 1;
  data.artBonus = 1;

  COMPONENT_INIT(self, COMP_SCHOOLLOGIC, data);
  self->events.logicUpdate = comp_schoolLogic_logicUpdate;
}