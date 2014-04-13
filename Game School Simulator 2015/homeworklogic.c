/******************************************************************************
Filename: homeworklogic.c

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "homeworklogic.h"
#include "sound.h"
#include "cloud.h"
#include "random.h"
#include "mousebox.h"

void comp_homeworkLogic_initialize(COMPONENT *self, void *event) {
  CDATA_HOMEWORKLOGIC *comData = (CDATA_HOMEWORKLOGIC *)self->data;
}

void comp_homeworkLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_HOMEWORKLOGIC *comData = (CDATA_HOMEWORKLOGIC *)self->data;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);

  if (mbox->left.pressed) {

  }
}

void comp_homeworkLogic(COMPONENT *self) {
  CDATA_HOMEWORKLOGIC data = {0};

  COMPONENT_INIT(self, COMP_HOMEWORKLOGIC, data);
  self->events.logicUpdate = comp_homeworkLogic_logicUpdate;
}