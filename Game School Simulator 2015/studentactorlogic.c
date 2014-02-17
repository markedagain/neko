/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentactorlogic.h"
#include "genericsprite.h"
#include "multisprite.h"

void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTACTOR *data = (CDATA_STUDENTACTOR *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
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


  data->timer += (float)updateEvent->dt;
  if (data->timer > data->lifetime)
    entity_destroy(self->owner);
}

void comp_studentActorLogic(COMPONENT *self) {
  CDATA_STUDENTACTOR data = { 0 };
  COMPONENT_INIT(self, COMP_STUDENTACTORLOGIC, data);
  self->events.logicUpdate = comp_studentActorLogic_logicUpdate;
}
