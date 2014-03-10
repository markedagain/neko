/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactorlogic.h"
#include "genericsprite.h"
#include "multisprite.h"
#include "random.h"
#include "studentmanagerlogic.h"

#define STUDENT_OFFSET 8.0f
#define FADE_TIME 1.0f

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  VEC3 pos = { 0 };

  if (!data->setSprite) {
    VEC3 position = { 0 };
    COMPONENT *multiSprite = entity_getComponent(self->owner, COMP_MULTISPRITE);
    ENTITY *legs;
    ENTITY *head;
    ENTITY *face;
    ENTITY *body;
    ENTITY *hair;

    // creating the generic sprites
    legs = genericSprite_create(self->owner->space, &position, NULL, data->legs);
    head = genericSprite_create(self->owner->space, &position, NULL, data->head);
    face = genericSprite_create(self->owner->space, &position, NULL, data->face);
    body = genericSprite_create(self->owner->space, &position, NULL, data->body);
    hair = genericSprite_create(self->owner->space, &position, NULL, data->hair);

    // setting the student actor's multisprite
    multiSprite_addSprite(multiSprite, legs);
    multiSprite_addSprite(multiSprite, head);
    multiSprite_addSprite(multiSprite, face);
    multiSprite_addSprite(multiSprite, body);
    multiSprite_addSprite(multiSprite, hair);

    data->setSprite = true;
  }

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
    if (data->timer > FADE_TIME) {
      ENTITY *manager = space_getEntity(self->owner->space, "studentManager");
      COMPONENT *managerLogic = entity_getComponent(manager, COMP_STUDENTMANAGERLOGIC);
      CDATA_STUDENTMANAGER *managerData = (CDATA_STUDENTMANAGER *)entity_getComponentData(manager, COMP_STUDENTMANAGERLOGIC);
      
      //when the student fades out, remove him from the drawnStudents list
      // this is messed uuup
      list_remove(managerData->drawnStudents, comp_studentManagerLogic_findStudent(managerLogic, self->owner, FT_ACTOR));
      entity_destroy(self->owner);
    }
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
