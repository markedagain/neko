/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptextlogic.h"
#include "transform.h"
#include "multisprite.h"

static void rise_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  trans->translation.y = action_ease(action, EASING_QUAD_OUT, data->startY, 32.0f);
}

static void riseStay_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  trans->translation.y = action_ease(action, EASING_QUINTIC_OUT, data->startY, 32.0f);//action_ease(action, EASING_QUAD_OUT, data->startY, data->startY + 0.8f);
}

static void rise_onStart(ACTION *action) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  data->startY = trans->translation.y;
}

static void fade_update(ACTION *action, double dt) {
  COMPONENT *self = (COMPONENT *)(action->data);
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  COMPONENT *multi = (COMPONENT *)entity_getComponent(self->owner, COMP_MULTISPRITE);
  multiSprite_setAlpha(multi, 1.0f - action_getEase(action, EASING_QUAD_OUT));
}

static void destroySelf_onEnd(ACTION *action) {
  COMPONENT *self = (COMPONENT *)(action->data);
  entity_destroy(self->owner);
}

void comp_popTextLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_TRANSFORM *parentTrans = (self->owner->parent == NULL ? NULL : (CDATA_TRANSFORM *)entity_getComponentData(self->owner->parent, COMP_TRANSFORM));

  if (!data->started) {
    data->started = true;

    switch (data->type) {
    case POPTYPE_DEFAULT:
      al_pushFront(&data->actions, action_create(self, rise_update, rise_onStart, NULL, true, 0.5f * data->duration));
      break;

    case POPTYPE_STAY:
      al_pushFront(&data->actions, action_create(self, riseStay_update, rise_onStart, NULL, true, 0.5f * data->duration));
      break;

    case POPTYPE_GROW:
      break;
    }
    al_pushBack(&data->actions, action_create(self, fade_update, NULL, destroySelf_onEnd, true, 0.5f * data->duration));
  }

  if (parentTrans && parentTrans->scale.x < 0)
    trans->scale.x = -1.0f;
  else
    trans->scale.x = 1.0f;

  al_update(&data->actions, updateEvent->dt);
}

void comp_popTextLogic_destroy(COMPONENT *self, void *event) {
  CDATA_POPTEXT *data = (CDATA_POPTEXT *)self->data;
  al_destroy(&data->actions);
}

void comp_popTextLogic(COMPONENT *self) {
  CDATA_POPTEXT data;
  data.type = POPTYPE_DEFAULT;
  al_init(&data.actions);
  data.started = false;
  COMPONENT_INIT(self, COMP_POPTEXTLOGIC, data);
  self->events.logicUpdate = comp_popTextLogic_logicUpdate;
  self->events.destroy = comp_popTextLogic_destroy;
}
