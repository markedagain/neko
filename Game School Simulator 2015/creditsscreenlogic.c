/******************************************************************************
Filename: creditsscreenlogic.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "creditsscreenlogic.h"
#include "mousebox.h"

static void fadeOut_update(ACTION *action, double dt) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self, COMP_SPRITE);

  sprite->color.a = 1.0f - action_getEase(action, EASING_QUAD_IN);
}

static void fadeOut_onEnd(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_CREDITS *creditsData = (CDATA_CREDITS *)entity_getComponentData(self, COMP_CREDITSSCREENLOGIC);
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self, COMP_MOUSEBOX);
    
  mbox->active = false;
  creditsData->finishedFading = true;
}

static void fadeOut_onStart(ACTION *action) {
  ENTITY *self = (ENTITY *)action->data;
  CDATA_CREDITS *creditsData = (CDATA_CREDITS *)entity_getComponentData(self, COMP_CREDITSSCREENLOGIC);

  creditsData->finishedFading = false;
}



void comp_creditsScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_CREDITS *data = (CDATA_CREDITS *)self->data;

  al_update(&data->actions, self->owner->space->game->systems.time.dt);

  if (mbox->left.pressed && data->finishedFading)
    al_pushBack(&data->actions, action_create(self->owner, fadeOut_update, fadeOut_onStart, fadeOut_onEnd, false, 0.5f));

}

void comp_creditsScreenLogic(COMPONENT *self) {
  CDATA_CREDITS data = { 0 };
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_CREDITSSCREENLOGIC, data);
  self->events.logicUpdate = comp_creditsScreenLogic_logicUpdate;
  self->events.initialize = comp_creditsScreenLogic_initialize;
}

void comp_creditsScreenLogic_initialize(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE  *)entity_getComponentData(self->owner, COMP_SPRITE);

  mbox->active = false;
  sprite->color.a = 0.0f;
}