/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentmanagerlogic.h"
#include "schoollogic.h"
#include "studentactor.h"
#include "transform.h"
#include "studentactorlogic.h"
#include "random.h"
#include "multisprite.h"
#include "genericsprite.h"
#include <stdio.h>

#define GROUND_HEIGHT 24
#define SPAWN_TIMER 2.0f

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
  int count = 0;
  int listCurr = 0;
  LIST_NODE *pNode;
  int choice;
  SPACE *sim = game_getSpace(self->owner->space->game, "sim");
  CDATA_SCHOOLLOGIC *schoolData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(space_getEntity(sim, "gameManager"), COMP_SCHOOLLOGIC);
  LIST_NODE *studentPtr = schoolData->students->first;
  CDATA_STUDENTDATA *studentData = 0;// = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);

  if (studentPtr) {
    studentData = (CDATA_STUDENTDATA *)entity_getComponentData((ENTITY *)studentPtr->data, COMP_STUDENTDATA);
  }

  comp_schoolLogic_findRooms(self, roomList);
  
  pNode = roomList->first;
  while (pNode) {
    ++count;
    pNode = pNode->next;
  }

  pNode = roomList->first;

  if (count == 1) {
    VEC3 *room = (VEC3 *)pNode->data;
    VEC3 pos = {(room->x - 7.5f) * 80.0f, (2 - room->y) * 80.0f + 20.0f, 0};
    SPACE *fg = game_getSpace(self->owner->space->game, "fg");
    ENTITY *studentActor = space_addEntityAtPosition(fg, arch_studentActor, "studentActor", &pos);
    studentManager_setStudent(studentActor, room, &pos, studentData);
    studentManager_deleteList(roomList);
    return;
  }
  
  else {
    // change this to be less poopy
    while (pNode) {
      ++listCurr;
      choice = randomIntRange(1, count);
      if (choice == 1) {
        VEC3 *room = (VEC3 *)pNode->data;
        VEC3 pos = {(room->x - 7.5f) * 80.0f, (2 - room->y) * 80.0f + 20.0f, 0};
        SPACE *fg = game_getSpace(self->owner->space->game, "fg");
        ENTITY *studentActor = space_addEntityAtPosition(fg, arch_studentActor, "studentActor", &pos);
        studentManager_setStudent(studentActor, room, &pos, studentData);
        studentManager_deleteList(roomList);
        return;
      }
      pNode = pNode->next;
      if (listCurr == count)
        pNode = roomList->first;
    }
  }
  studentManager_deleteList(roomList);
}

void studentManager_deleteList(LIST *list) {
  LIST_NODE *pNode = list->first;
  while (pNode) {
    free(pNode->data);
    pNode = pNode->next;
  }
  list_destroy(list);
}

void studentManager_setStudent(ENTITY *studentActor, const VEC3 *room, const VEC3 *pos, CDATA_STUDENTDATA *studentData) {
  CDATA_TRANSFORM *studentTrans = (CDATA_TRANSFORM *)entity_getComponentData(studentActor, COMP_TRANSFORM);
  CDATA_STUDENTACTOR *actorData = (CDATA_STUDENTACTOR *)entity_getComponentData(studentActor, COMP_STUDENTACTORLOGIC);
  COMPONENT *multiSprite = entity_getComponent(studentActor, COMP_MULTISPRITE);
  VEC3 position = { 0 };
  char spriteName[21];
  ENTITY *legs;
  ENTITY *head;
  ENTITY *face;
  ENTITY *body;
  ENTITY *hair;

  if (studentData == 0)
    return;

  // string pool troubs
  sprintf(spriteName, "student/male/legs/%.2d", studentData->legs);
  legs = genericSprite_create(studentActor->space, &position, NULL, "student/male/legs/02");
  
  sprintf(spriteName, "student/male/head/%.2d", studentData->head);
  head = genericSprite_create(studentActor->space, &position, NULL, "student/male/head/02");

  sprintf(spriteName, "student/male/face/%.2d", studentData->face);
  face = genericSprite_create(studentActor->space, &position, NULL, "student/male/face/02");

  sprintf(spriteName, "student/male/body/%.2d", studentData->body);
  body = genericSprite_create(studentActor->space, &position, NULL, "student/male/body/02");

  sprintf(spriteName, "student/male/hair/%.2d", studentData->hair);
  hair = genericSprite_create(studentActor->space, &position, NULL, "student/male/hair/02");

  multiSprite_addSprite(multiSprite, legs);
  multiSprite_addSprite(multiSprite, head);
  multiSprite_addSprite(multiSprite, face);
  multiSprite_addSprite(multiSprite, body);
  multiSprite_addSprite(multiSprite, hair);
  actorData->lifetime = 5.0f;
  actorData->roomSize = room->z * 80.0f;
  actorData->origin = pos->x;
}

void comp_studentManagerLogic(COMPONENT *self) {
  CDATA_STUDENTMANAGER data = { 0 };
  COMPONENT_INIT(self, COMP_STUDENTMANAGERLOGIC, data);
  self->events.logicUpdate = comp_studentManagerLogic_logicUpdate;
}
