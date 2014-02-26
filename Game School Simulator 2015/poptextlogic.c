/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptextlogic.h"
#include "transform.h"
#include "multisprite.h"

#define FADESPEED 0.08
#define GROWSPEED 0.06

void comp_popTextLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  data->timer -= (float)updateEvent->dt;
  switch (data->type) {

  case POPTYPE_DEFAULT:
    if (data->timer <= 0.0f) {
      COMPONENT *multi = entity_getComponent(self->owner, COMP_MULTISPRITE);
      data->alpha -= (float)FADESPEED;
      if (data->alpha < 0.0f)
        data->alpha = 0.0f;
      multiSprite_setAlpha(multi, data->alpha);
    }
    if (data->timer <= 0.0f && data->alpha <= 0.0f)
      entity_destroy(self->owner);
    trans->translation.y += 0.5f;
    break;

  case POPTYPE_STAY:
    if (data->timer <= 0.0f) {
      COMPONENT *multi = entity_getComponent(self->owner, COMP_MULTISPRITE);
      data->alpha -= (float)FADESPEED;
      if (data->alpha < 0.0f)
        data->alpha = 0.0f;
      multiSprite_setAlpha(multi, data->alpha);
    }
    if (data->timer >= data->maxTimer * 0.35f) {
      trans->translation.y += 0.5f;
    }
    if (data->timer <= 0.0f && data->alpha <= 0.0f)
      entity_destroy(self->owner);
    break;

  case POPTYPE_GROW:
    if (data->timer <= 0.0f) {
      COMPONENT *multi = entity_getComponent(self->owner, COMP_MULTISPRITE);
      data->alpha -= (float)FADESPEED;
      if (data->alpha < 0.0f)
        data->alpha = 0.0f;
      multiSprite_setAlpha(multi, data->alpha);
      trans->scale.x += (float)GROWSPEED;
      trans->scale.y += (float)GROWSPEED;
    }
    if (data->timer <= 0.0f && data->alpha <= 0.0f)
      entity_destroy(self->owner);
    trans->translation.y += 0.5f;
    break;

  }
}

void comp_popTextLogic(COMPONENT *self) {
  CDATA_POPTEXT data = { 0 };
  data.timer = 1.0f;
  data.maxTimer = 1.0f;
  data.alpha = 1.0f;
  data.type = POPTYPE_DEFAULT;
  COMPONENT_INIT(self, COMP_POPTEXTLOGIC, data);
  self->events.logicUpdate = comp_popTextLogic_logicUpdate;
}
