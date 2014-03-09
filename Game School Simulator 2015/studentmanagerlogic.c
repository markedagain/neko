/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentmanagerlogic.h"
#include "schoollogic.h"
#include "studentactor.h"
#include "transform.h"
#include "studentactorlogic.h"
#include "random.h"
#include "multisprite.h"
#include "genericsprite.h"
#include "poptext.h"
#include <stdio.h>

#define GROUND_HEIGHT 24
#define SPAWN_TIMER 2.0f
#define MAX_STUDENTS 1000

// this totally works except it derps out if you build a building just as a new student spawns

void comp_studentManagerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_STUDENTMANAGER *data = (CDATA_STUDENTMANAGER *)self->data;

  data->timer += (float)updateEvent->dt;
  if(data->timer > SPAWN_TIMER) {
    studentManager_spawnStudent(self);
    data->timer = 0.0f;
  }
}

void studentManager_spawnStudent(COMPONENT *self) {
  LIST *roomList = list_create();
  LIST *studentList = list_create();
  int listCurr = 0;
  LIST_NODE *pNode;
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  LIST_NODE *studentPtr;
  CDATA_STUDENTDATA *studentData = 0;
  CDATA_STUDENTMANAGER *data = (CDATA_STUDENTMANAGER *)self->data;
  int numStudents = 0;
  int randomIndex = 0;
  int roomCount = schoolData->roomCount;
  int count = 1;

  // make a copy of the list of students, then remove the ones already drawn
  list_copy(studentList, schoolData->students);
  pNode = data->drawnStudents->first;
  while (pNode) {
    list_remove(studentList, list_getNode(studentList, ((COMPLETE_STUDENT *)pNode->data)->simStudent));
    pNode = pNode->next;
  }

  // roll to the random student
  studentPtr = studentList->first;
  // if no students, return
  if (!studentPtr)
    return;
  numStudents = studentList->count;
  randomIndex = randomIntRange(1, numStudents);
  while (count < randomIndex) {
    ++count;
    studentPtr = studentPtr->next;
  }

  // get the random student's data
  studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);

  // get all the currently built rooms' data
  comp_schoolLogic_findRooms(self, roomList);
  
  // roll to random room
  pNode = roomList->first;
  randomIndex = randomIntRange(1, roomCount);
  count = 1;
  while (count < randomIndex) {
    pNode = pNode->next;
    ++count;
  }

  // spawn the student
  {
    COMPLETE_STUDENT *newStudent = (COMPLETE_STUDENT *)malloc(sizeof(COMPLETE_STUDENT));
    VEC3 *room = (VEC3 *)pNode->data;
    VEC3 pos = {(room->x - 7.5f) * 80.0f, (2 - room->y) * 80.0f + 20.0f, 0};
    SPACE *fg = game_getSpace(self->owner->space->game, "fg");
    ENTITY *studentActor = space_addEntityAtPosition(fg, arch_studentActor, "studentActor", &pos);
    int ID = data->currID;
    if (data->currID > MAX_STUDENTS) {
      data->currID = 1;
      ID = 1;
    }
    newStudent->simStudent = (ENTITY *)studentPtr->data;
    newStudent->studentActor = studentActor;
    list_insert_end(data->drawnStudents, newStudent);
    studentManager_setStudent(studentActor, room, &pos, studentData, (ENTITY *)(studentPtr->data), ID);
  }

  studentManager_deleteList(roomList);
  list_destroy(studentList);
}

void studentManager_deleteList(LIST *list) {
  LIST_NODE *pNode = list->first;
  while (pNode) {
    free(pNode->data);
    pNode = pNode->next;
  }
  list_destroy(list);
}

void studentManager_setStudent(ENTITY *studentActor, const VEC3 *room, const VEC3 *pos, CDATA_STUDENTDATA *studentData, ENTITY *studentPtr, int ID) {
  CDATA_TRANSFORM *studentTrans = (CDATA_TRANSFORM *)entity_getComponentData(studentActor, COMP_TRANSFORM);
  CDATA_STUDENTACTOR *actorData = (CDATA_STUDENTACTOR *)entity_getComponentData(studentActor, COMP_STUDENTACTORLOGIC);
  char spriteName[30];

  if (studentData == 0)
    return;

  actorData->studentPtr = studentPtr;

  if (studentData->gender == GEN_MALE) {
    sprintf(spriteName, "student/male/legs/%.2d", studentData->legs);
    strcpy(actorData->legs, spriteName);
  
    sprintf(spriteName, "student/male/head/%.2d", studentData->head);
    strcpy(actorData->head, spriteName);

    sprintf(spriteName, "student/male/face/%.2d", studentData->face);
    strcpy(actorData->face, spriteName);

    sprintf(spriteName, "student/male/body/%.2d", studentData->body);
    strcpy(actorData->body, spriteName);

    sprintf(spriteName, "student/male/hair/%.2d", studentData->hair);
    strcpy(actorData->hair, spriteName);
  }
  else {
    sprintf(spriteName, "student/female/legs/%.2d", studentData->legs);
    strcpy(actorData->legs, spriteName);
  
    sprintf(spriteName, "student/female/head/%.2d", studentData->head);
    strcpy(actorData->head, spriteName);

    sprintf(spriteName, "student/female/face/%.2d", studentData->face);
    strcpy(actorData->face, spriteName);

    sprintf(spriteName, "student/female/body/%.2d", studentData->body);
    strcpy(actorData->body, spriteName);

    sprintf(spriteName, "student/female/hair/%.2d", studentData->hair);
    strcpy(actorData->hair, spriteName);
  }

  actorData->ID = ID;
  actorData->lifetime = 5.0f;
  actorData->roomSize = room->z * 80.0f;
  actorData->origin = pos->x;
}

void comp_studentManagerLogic(COMPONENT *self) {
  CDATA_STUDENTMANAGER data = { 0 };
  data.drawnStudents = list_create();
  COMPONENT_INIT(self, COMP_STUDENTMANAGERLOGIC, data);
  self->events.logicUpdate = comp_studentManagerLogic_logicUpdate;
  self->events.destroy = comp_studentManagerLogic_destroy;
}

void comp_studentManagerLogic_destroy(COMPONENT *self, void *event) {
  CDATA_STUDENTMANAGER* data = (CDATA_STUDENTMANAGER *)self->data;

  list_destroy(data->drawnStudents);
}

void comp_studentManagerLogic_statGainText(COMPONENT *studentManagerLogic) {
  CDATA_STUDENTMANAGER *data = (CDATA_STUDENTMANAGER *)studentManagerLogic->data;
  LIST_NODE *pStudent = data->drawnStudents->first;
  VEC3 position;
  char buffer[20];
  VEC4 color = { 0, 0, 0, 1.0f };

  while (pStudent) {
    ENTITY *simStudent = ((COMPLETE_STUDENT *)pStudent->data)->simStudent;
    ENTITY *studentActor = ((COMPLETE_STUDENT *)pStudent->data)->studentActor;
    CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(studentActor, COMP_TRANSFORM);
    CDATA_STUDENTDATA *studentData = (CDATA_STUDENTDATA *)entity_getComponentData(simStudent, COMP_STUDENTDATA);
    switch (studentData->major) {
    case M_TECH:
      sprintf(buffer, "Tech + %f", studentData->techIncrease);
      break;
    case M_ART:
      sprintf(buffer, "Art + %f", studentData->techIncrease);
      break;
    case M_DESIGN:
      sprintf(buffer, "Design + %f", studentData->techIncrease);
      break;
    }
    position = trans->translation;
    popText_create(studentManagerLogic->owner->space, &position, "getStatsText", "fonts/gothic/12", buffer, &color, POPTYPE_STAY, 4.0f);
  
    pStudent = pStudent->next;
  }

}

// find the student actor then return its node
LIST_NODE *comp_studentManagerLogic_findStudent(COMPONENT *studentManagerLogic, ENTITY *actor) {
  CDATA_STUDENTMANAGER *data = (CDATA_STUDENTMANAGER *)studentManagerLogic->data;
  LIST_NODE *pStudent = data->drawnStudents->first;

  while (pStudent) {
    if (((COMPLETE_STUDENT *)(pStudent->data))->studentActor == actor)
      return pStudent;
    pStudent = pStudent->next;
  }

  return NULL;
}