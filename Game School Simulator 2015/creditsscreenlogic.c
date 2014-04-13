/******************************************************************************
Filename: creditsscreenlogic.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "creditsscreenlogic.h"
#include "mousebox.h"

void comp_creditsScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  if (mbox->left.pressed)
    entity_destroy(self->owner);

}

void comp_creditsScreenLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_CREDITSSCREENLOGIC);
  self->events.logicUpdate = comp_creditsScreenLogic_logicUpdate;
  self->events.initialize = comp_creditsScreenLogic_initialize;
}

void comp_creditsScreenLogic_initialize(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE  *)entity_getComponentData(self->owner, COMP_SPRITE);

  mbox->active = false;
  sprite->color.a = 0.0f;
}