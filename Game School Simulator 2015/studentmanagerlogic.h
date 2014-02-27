/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTMANAGERLOGIC__
#define __COMP_STUDENTMANAGERLOGIC__

#include "entity.h"
#include "hash.h"
#include "studentdata.h"

#define COMP_STUDENTMANAGERLOGIC HASH("COMP_STUDENTMANAGERLOGIC")
void comp_studentManagerLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentManagerLogic(COMPONENT *self);
void studentManager_spawnStudent(COMPONENT *self);
void studentManager_setStudent(ENTITY *studentActor, const VEC3 *room, const VEC3 *pos, CDATA_STUDENTDATA *studentData) ;
void studentManager_deleteList(LIST *list);

typedef struct {
  float timer;
} CDATA_STUDENTMANAGER;

#endif
