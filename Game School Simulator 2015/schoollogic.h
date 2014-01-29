/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SCHOOLLOGIC__
#define __COMP_SCHOOLLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/linkedlist.h"
#include "roomlogic.h"

#define COMP_SCHOOLLOGIC HASH("COMP_SCHOOLLOGIC")
#define MAX_FLOORS 3
#define MAX_ROOMS_PER_FLOOR 16

typedef struct cdata_schoolLogic_t {
  char *schoolName;
  long int money;
  int tuition;
  int studentCapacity;
  int currentStudents;
  int incomingStudents;
  LIST *students;
  LIST *alumni;
  int roomMaintainance;
  LIST *roomList;
  int reputation;
  int techBonus;
  int designBonus;
  int artBonus;
  union {
    ENTITY *coord[MAX_FLOORS][MAX_ROOMS_PER_FLOOR];
  } rooms;
} CDATA_SCHOOLLOGIC;

void comp_schoolLogic_logicUpdate(COMPONENT *, void *);
void comp_schoolLogic_initialize(COMPONENT *self, void *event);
void comp_schoolLogic_destroy(COMPONENT *, void *);
void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_constructRoom(COMPONENT *self, CDATA_SCHOOLLOGIC *comData, ROOM_TYPE roomType);
void comp_schoolLogic_listRooms(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_listStudents(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_listAlumni(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic(COMPONENT *);

#endif