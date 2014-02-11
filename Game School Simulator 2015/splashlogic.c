/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "splashlogic.h"
#include "sound.h"

void comp_splashLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_SPLASHLOGIC *data = (CDATA_SPLASHLOGIC *)self->data;
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  data->timer -= (float)updateEvent->dt;
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
  if (!data->playedSound) {
    data->playedSound = true;
    sound_playSound(&self->owner->space->game->systems.sound, "logo");
  }
}

void comp_splashLogic(COMPONENT *self) {
  CDATA_SPLASHLOGIC data = { 0 };
  data.playedSound = false;
  data.timer = 3.0f;
  COMPONENT_INIT(self, COMP_SPLASHLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_splashLogic_logicUpdate;
}