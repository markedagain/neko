/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "management.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "playerlogic.h"
#include "roomlogic.h"
#include "UI_build.h"
#include "schoollogic.h"
#include "managescreen.h"
#include "managescreenlogic.h"

void comp_manageScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MANAGESCREEN *data = (CDATA_MANAGESCREEN *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  SPACE *simSpace = game_getSpace(self->owner->space->game, "sim");
  SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  ENTITY *schoolData = space_getEntity(simSpace, "gameManager");
  ENTITY *updateData = space_getEntity(uiSpace, "manage_button");
  CDATA_SCHOOLLOGIC *comData = (CDATA_SCHOOLLOGIC *)entity_getComponentData(schoolData, COMP_SCHOOLLOGIC);
  CDATA_MANAGEMENT *managementData = (CDATA_MANAGEMENT *)entity_getComponentData(updateData, COMP_MANAGEMENT);

  // Check if current management values have changed for...
  // Expected Income
  if (comData->currentStudents != managementData->currStudentPop || comData->tuition != managementData->currTuition) {
    managementData->expectedIncome = comData->currentStudents * comData->tuition;
    sprintf(managementData->incomeBuffer, "$%i", managementData->expectedIncome);
    genericText_setText(managementData->income, managementData->incomeBuffer);
  }
  
  // Incoming Students
  if (comData->incomingStudents != managementData->currStudentInc) {
    managementData->currStudentInc = comData->incomingStudents;
    sprintf(managementData->studentIncBuffer, "%i", comData->incomingStudents);
    genericText_setText(managementData->studentInc, managementData->studentIncBuffer);
  }

  // Tuition
  if (comData->tuition != managementData->currTuition) {
    managementData->currTuition = comData->tuition;
    sprintf(managementData->tuitionBuffer, "$%i", comData->tuition);
    genericText_setText(managementData->tuition, managementData->tuitionBuffer);
  }

  // Minimum GPA
  if (comData->minGpa != managementData->currMinGpa) {
    managementData->currMinGpa = comData->minGpa;
    sprintf(managementData->gpaBuffer, "%g", comData->minGpa);
    genericText_setText(managementData->gpa, managementData->gpaBuffer);
  }

  // Student Population
  if (comData->currentStudents != managementData->currStudentPop) {
    managementData->currStudentPop = comData->currentStudents;
    sprintf(managementData->studentPopBuffer, "%i / %i", comData->currentStudents, comData->studentCapacity);
    genericText_setText(managementData->studentPop, managementData->studentPopBuffer);
  }

  // Upkeep Costs
  if (comData->roomMaintenance != managementData->currUpkeep) {
    managementData->currUpkeep = comData->roomMaintenance;
    sprintf(managementData->costsBuffer, "-$%i", comData->roomMaintenance);
    genericText_setText(managementData->currCosts, managementData->costsBuffer);
  }

  // Reputation
  if (comData->reputation != managementData->currReputation) {
    managementData->currReputation = comData->reputation;
    sprintf(managementData->reputationBuffer, "%i", comData->reputation);
    genericText_setText(managementData->rep, managementData->reputationBuffer);
  }
}

void comp_manageScreenLogic(COMPONENT *self) {
  VEC3 position = { 0, 0, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  CDATA_MANAGESCREEN data = { 0 };

  // SPACE *uiSpace = game_getSpace(self->owner->space->game, "ui");
  vec3_set(&position, -50, 70, 0);
  //data.leftGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_left");
  vec3_set(&position, -50, 70, 0);
  //data.rightGPA = genericSprite_create(uiSpace, &position, NULL, "cursor/manage_button_right");
  COMPONENT_INIT(self, COMP_MANAGESCREENLOGIC, data);
  self->events.logicUpdate = comp_manageScreenLogic_logicUpdate;
}
