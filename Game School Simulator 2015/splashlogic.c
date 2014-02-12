/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "splashlogic.h"
#include "sound.h"

void comp_splashLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_SPLASHLOGIC *data = (CDATA_SPLASHLOGIC *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  ENTITY *bg = space_getEntity(self->owner->space, "splash_bg");
  data->timer -= (float)updateEvent->dt;
  if (bg && data->fadeBackground) {
    CDATA_SPRITE *bgSprite = (CDATA_SPRITE *)entity_getComponentData(bg, COMP_SPRITE);
    bgSprite->color.a -= 0.01f;
    if (bgSprite->color.a <= 0.0f) {
      sprite->source = "splash";
      data->secondLogo = true;
      data->timer = 3.0f;
      sound_playSound(&self->owner->space->game->systems.sound, "logo");
      data->fadeBackground = false;
      entity_destroy(bg);
    }
  }
  if (data->secondLogo) {
    if (data->timer <= 0.0f) {
      sprite->color.a -= 0.05f;
      if (sprite->color.a <= 0) {
        sprite->color.a = 0;
        entity_destroy(self->owner);
      }
    }
    else {
      sprite->color.a += 0.026f;
      if (sprite->color.a >= 1.0f) {
        sprite->color.a = 1.0f;
      }
    }
  }
  else {
    if (data->timer <= 0.0f) {
      sprite->color.a -= 0.05f;
      if (sprite->color.a <= 0) {
        sprite->color.a = 0;
        data->fadeBackground = true;
      }
    }
    else {
      sprite->color.a += 0.026f;
      if (sprite->color.a >= 1.0f) {
        sprite->color.a = 1.0f;
      }
    }
  }
}

void comp_splashLogic(COMPONENT *self) {
  CDATA_SPLASHLOGIC data = { 0 };
  data.secondLogo = false;
  data.fadeBackground = false;
  data.timer = 3.0f;
  COMPONENT_INIT(self, COMP_SPLASHLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_splashLogic_logicUpdate;
}