/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTMANAGERLOGIC__
#define __COMP_STUDENTMANAGERLOGIC__

#include "entity.h"
#include "hash.h"
#include "studentdata.h"

#define COMP_STUDENTMANAGERLOGIC HASH("COMP_STUDENTMANAGERLOGIC")

typedef struct {
  float timer;
  LIST *drawnStudents;
  int currID;
  int displayTotal;
  int displayCurrent;
} CDATA_STUDENTMANAGER;

typedef struct {
  ENTITY *simStudent;
  ENTITY *studentActor;
} COMPLETE_STUDENT;

typedef enum {
  FT_SIM,
  FT_ACTOR
}FIND_TYPE;


void comp_studentManagerLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentManagerLogic(COMPONENT *self);
void studentManager_spawnStudent(COMPONENT *self);
void studentManager_setStudent(ENTITY *studentActor, const VEC3 *room, const VEC3 *pos, CDATA_STUDENTDATA *studentData, ENTITY *studentPtr, int ID);
void studentManager_deleteList(LIST *list);
void comp_studentManagerLogic_destroy(COMPONENT *self, void *event);
LIST_NODE *comp_studentManagerLogic_findStudent(COMPONENT *studentManagerLogic, ENTITY *target, FIND_TYPE type);
void comp_studentManagerLogic_statGainText(COMPONENT *studentManagerLogic);
void comp_studentManagerLogic_removeGraduate(COMPONENT *studentManagerLogic, ENTITY *student);
void comp_studentManagerLogic_removeDropout(COMPONENT *studentManagerLogic, ENTITY *student);
void comp_studentManagerLogic_updateDisplayFraction(COMPONENT *self);

#endif
