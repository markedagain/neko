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
  float minIncomingGpa;
  float minGpa;
  int studentCapacity;
  int currentStudents;
  int incomingStudents;
  int expectedGraduates;
  LIST *students;
  LIST *alumni;
  int roomMaintenance;
  int slotsUsed;
  LIST *roomList;
  int roomCount;
  int reputation;
  int techBonus;
  int designBonus;
  int artBonus;
  int semTech;
  int semDesign;
  int semArt;
  int motivationBonus;
  BOOL roomConstructed;
  long int currMoney;
  int counter;
  ENTITY *moneyUI;
  ENTITY *studentUI;
  char buffer[20];
  int roomFlag[13];
  union {
    ENTITY *coord[MAX_FLOORS][MAX_ROOMS_PER_FLOOR];
  } rooms;
} CDATA_SCHOOLLOGIC;

void comp_schoolLogic_logicUpdate(COMPONENT *, void *);
void comp_schoolLogic_frameUpdate(COMPONENT *, void *);
void comp_schoolLogic_initialize(COMPONENT *self, void *event);
void comp_schoolLogic_destroy(COMPONENT *, void *);
void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_findBuildSpots(COMPONENT *ptr, ROOM_TYPE roomType, int roomSize, LIST *legalSlots);
void comp_schoolLogic_constructRoom(COMPONENT *ptr, ROOM_TYPE roomType, int roomSize, int floorToUse, int colToUse);
int comp_schoolLogic_getRoomSize(ROOM_TYPE type);
void comp_schoolLogic_listRooms(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_listStudents(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_listAlumni(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_millionaire(COMPONENT *ptr);
void comp_schoolLogic(COMPONENT *);
void comp_schoolLogic_findRooms(COMPONENT *comp, LIST *roomList);

#endif