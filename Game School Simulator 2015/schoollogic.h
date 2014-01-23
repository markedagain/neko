/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_SCHOOLLOGIC__
#define __COMP_SCHOOLLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/linkedlist.h"

#define COMP_SCHOOLLOGIC HASH("COMP_SCHOOLLOGIC")

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
  LIST *rooms;
  int reputation;
} CDATA_SCHOOLLOGIC;

void comp_schoolLogic_logicUpdate(COMPONENT *, void *);
void comp_schoolLogic_destroy(COMPONENT *, void *);
void comp_schoolLogic_updateDataMonth(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataSemester(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic_updateDataYear(COMPONENT *self, CDATA_SCHOOLLOGIC *comData);
void comp_schoolLogic(COMPONENT *);

#endif