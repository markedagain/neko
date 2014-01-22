/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentdata.h"
#include "random.h"
#include <string.h>
#include <malloc.h>
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"


void comp_studentData_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_STUDENTDATA *comData = (CDATA_STUDENTDATA *)self->data;
  //INPUT_CONTAINER *input = &self->owner->space->game->input;

  printf("Name: %s %s\n", comData->name.first, comData->name.last);
  printf("Tech Skill: %d\n", comData->techSkill);
  printf("Art Skill: %d\n", comData->artSkill);
  printf("Design Skill: %d\n", comData->designSkill);
  printf("Motivation: %d\n", comData->motivation);
  printf("Year Started: %d\n", comData->yearStarted);
}

void comp_studentData(COMPONENT *self) {
  int lowValue = 0;
  int highValue = 99;
// unsigned short elapsedFrames = self->owner->space->game->systems.time.elapsedFrames;
  
  CDATA_STUDENTDATA student = { 0 };
  student.name.first = "Samuel";
  student.name.last = "Valdez";
  student.techSkill = randomIntRange(lowValue, highValue);
  student.artSkill = randomIntRange(lowValue, highValue);
  student.designSkill = randomIntRange(lowValue, highValue);
  student.motivation = randomIntRange(lowValue, highValue);
  student.yearStarted = 0;

  COMPONENT_INIT(self, COMP_STUDENTDATA, student);
  self->events.logicUpdate = comp_studentData_logicUpdate;
}