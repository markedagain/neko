/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactorlogic.h"
#include "genericsprite.h"
#include "multisprite.h"
#include "random.h"

#define STUDENT_OFFSET 8.0f
#define FADE_TIME 1.0f

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  VEC3 pos = { 0 };

  // fade in when spawned before moving
  if (data->fadeIn) {
    COMPONENT *multiSprite = (COMPONENT *)entity_getComponent(self->owner, COMP_MULTISPRITE);
    data->timer += (float)updateEvent->dt;
    multiSprite_setAlpha(multiSprite, data->timer / FADE_TIME);
    if (data->timer > FADE_TIME) {
      data->fadeIn = false;
      data->timer = 0.0f;
    }
  }

  // fading out logic
  else if (data->fadeOut) {
    COMPONENT *multiSprite = (COMPONENT *)entity_getComponent(self->owner, COMP_MULTISPRITE);
    data->timer += (float)updateEvent->dt;
    if (data->timer > FADE_TIME)
      entity_destroy(self->owner);
    multiSprite_setAlpha(multiSprite, 1 - data->timer / FADE_TIME);
  }

  // if not fading in or out
  else {
    data->timer += (float)updateEvent->dt;

    // if time is up, make pm walk towards door
    if (data->timer > data->lifetime) {
      // set velocity based on position relative to door, and flip sprite
      data->velocity = trans->translation.x > data->origin ? -1.0f : 1.0f;
      comp_studentActorLogic_flipSprite(self);

      // once i'm at the door, fadeout
      if (fabsf(trans->translation.x - data->origin) <= 0.1) {
        data->timer = 0.0f;
        data->fadeOut = true;
      }
    }

    // if time is not up, random behavior
    else {
      // make the students walk around
      data->timer2 += (float)updateEvent->dt;

      // if hitting the door
      if (trans->translation.x < data->origin - 40.0f + STUDENT_OFFSET || trans->translation.x > data->origin + data->roomSize - 40.0f - STUDENT_OFFSET) {

        data->velocity = -data->velocity;
        data->timer2 = 0.0f;
        comp_studentActorLogic_flipSprite(self);
      }

      // if walked for a certain amount of time
      if (data->timer2 > 0.5f && data->velocity == 0.0f) {
        int newVel = randomIntRange(0, 1);
        switch (newVel) {
        case (0):
        data->velocity = 1.0f;
          break;
        case(1):
          data->velocity = -1.0f;
          break;
        }
        data->timer2 = 0.0f;
        comp_studentActorLogic_flipSprite(self);
      }

      if (data->timer2 > 1.0f && data->velocity != 0.0f) {
        data->velocity = 0.0f;
        data->timer2 = 0.0f;
      }
    }
    // update 'physics'
    trans->translation.x += data->velocity;
  }
}

void comp_studentActorLogic_flipSprite(COMPONENT *self) {
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  
  if (data->velocity < 0)
    trans->scale.x = -1.0f;
  else
    trans->scale.x = 1.0f;
}

void comp_studentActorLogic(COMPONENT *self) {
  CDATA_STUDENTACTOR data = { 0 };
  COMPONENT_INIT(self, COMP_STUDENTACTORLOGIC, data);
  self->events.logicUpdate = comp_studentActorLogic_logicUpdate;
  self->events.initialize = comp_studentActorLogic_initialize;
}

void comp_studentActorLogic_initialize(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  int velocity = randomIntRange(0, 1);
  data->fadeIn = true;
  switch (velocity) {
  case (0):
    data->velocity = 1.0f;
    break;
  case(1):
    data->velocity = -1.0f;
    trans->scale.x = -1;
    break;
  }
}
