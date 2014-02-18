/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactorlogic.h"
#include "genericsprite.h"
#include "multisprite.h"
#include <stdlib.h>

#define STUDENT_OFFSET 8.0f

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  VEC3 pos = { 0 };
  
  // set the sprite
  if (!data->setSprite) {
    ENTITY *legs = genericSprite_create(self->owner->space, &pos, NULL, "student/male/legs/01");
    ENTITY *head = genericSprite_create(self->owner->space, &pos, NULL, "student/male/head/01");
    ENTITY *face = genericSprite_create(self->owner->space, &pos, NULL, "student/male/face/01");
    ENTITY *body = genericSprite_create(self->owner->space, &pos, NULL, "student/male/body/01");
    ENTITY *hair = genericSprite_create(self->owner->space, &pos, NULL, "student/male/hair/01");
    COMPONENT *multiSprite = entity_getComponent(self->owner, COMP_MULTISPRITE);

    multiSprite_addSprite(multiSprite, legs);
    multiSprite_addSprite(multiSprite, head);
    multiSprite_addSprite(multiSprite, face);
    multiSprite_addSprite(multiSprite, body);
    multiSprite_addSprite(multiSprite, hair);
    data->setSprite = true;
  }

  /*if (data->fadeIn) {
    
  }*/

  else {
    // if time is up, make pm walk towards door
    data->timer += (float)updateEvent->dt;
    if (data->timer > data->lifetime) {
      data->velocity = trans->translation.x > data->origin ? -1.0f : 1.0f;
      if (data->velocity < 0)
        trans->scale.x = -1.0f;
      else
        trans->scale.x = 1.0f;
      if (fabsf(trans->translation.x - data->origin) <= 0.1)
        entity_destroy(self->owner);
    }

    // if time is not up, random behavior
    else {
      // make the students walk around
      data->timer2 += (float)updateEvent->dt;
      if (trans->translation.x < data->origin - 40.0f + STUDENT_OFFSET || trans->translation.x > data->origin + data->roomSize - 40.0f - STUDENT_OFFSET) {
        data->velocity = -data->velocity;
        data->timer2 = 0.0f;
        if (data->velocity < 0)
          trans->scale.x = -1.0f;
        else
          trans->scale.x = 1.0f;
      }

      if (data->timer2 > 4.0f) {
        data->velocity = -data->velocity;
        data->timer2 = 0.0f;
        if (data->velocity < 0)
          trans->scale.x = -1.0f;
        else
          trans->scale.x = 1.0f;
      }
    }
    trans->translation.x += data->velocity;
  }
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
  int velocity = rand() % 2;
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
