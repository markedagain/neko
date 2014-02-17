/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentmanagerlogic.h"
#include "schoollogic.h"
#include "studentactor.h"
#include "transform.h"
#include "studentactorlogic.h"
#include <stdlib.h>

#define GROUND_HEIGHT 24

void comp_studentManagerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_STUDENTMANAGER *data = (CDATA_STUDENTMANAGER *)self->data;

  data->timer += (float)updateEvent->dt;
  if(data->timer > 3.0f) {
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
  comp_schoolLogic_findRooms(self, roomList);
  
  pNode = roomList->first;
  while (pNode) {
    ++count;
    pNode = pNode->next;
  }

  pNode = roomList->first;

  if (count == 1) {
    VEC3 *room = (VEC3 *)pNode->data;
    SPACE *fg = game_getSpace(self->owner->space->game, "fg");
    ENTITY *studentActor = space_addEntity(fg, arch_studentActor, "pm");
    studentManager_setStudent(studentActor, room);
    return;
  }
  
  else {
    while (pNode) {
      ++listCurr;
      choice = rand() % count;//randomIntRange(1, count);
      if (choice == 1) {
        VEC3 *room = (VEC3 *)pNode->data;
        VEC3 pos = {(room->x - 7.5f) * 80.0f, GROUND_HEIGHT + (2 - room->y) * 80.0f, 0};
        SPACE *fg = game_getSpace(self->owner->space->game, "fg");
        ENTITY *studentActor = space_addEntityAtPosition(fg, arch_studentActor, "pm", &pos);
        studentManager_setStudent(studentActor, room);
        return;
      }
      pNode = pNode->next;
      if (listCurr == count)
        pNode = roomList->first;
    }
  }
}

void studentManager_setStudent(ENTITY *studentActor, VEC3 *room) {
  CDATA_TRANSFORM *studentTrans = (CDATA_TRANSFORM *)entity_getComponentData(studentActor, COMP_TRANSFORM);
  CDATA_STUDENTACTOR *actorData = (CDATA_STUDENTACTOR *)entity_getComponentData(studentActor, COMP_STUDENTACTORLOGIC);

  actorData->lifetime = 10.0f;
}

void comp_studentManagerLogic(COMPONENT *self) {
  CDATA_STUDENTMANAGER data = { 0 };
  COMPONENT_INIT(self, COMP_STUDENTMANAGERLOGIC, data);
  self->events.logicUpdate = comp_studentManagerLogic_logicUpdate;
}
