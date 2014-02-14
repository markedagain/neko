/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "blackbarlogic.h"
#include "component.h"
#include "transform.h"
#include "sprite.h"
#include "entity.h"

void comp_blackBarLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_BLACKBARLOGIC *data = (CDATA_BLACKBARLOGIC *)self->data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);
  float screenAspectRatio = (float)self->owner->space->game->innerWindow.width / (float)self->owner->space->game->innerWindow.height;

  if (screenAspectRatio > self->owner->space->game->dimensions.aspectRatio) {
    sprite->visible = true;
    trans->scale.x = (self->owner->space->game->dimensions.aspectRatio - screenAspectRatio) * (float)self->owner->space->game->dimensions.width / 2.0f;
    trans->scale.y = (float)self->owner->space->game->innerWindow.height;
    trans->translation.y = 0;
    if (data->id == 0)
      trans->translation.x = (float)self->owner->space->game->dimensions.width / 2.0f - trans->scale.x / 2.0f;
    else
      trans->translation.x = -(float)self->owner->space->game->dimensions.width / 2.0f + trans->scale.x / 2.0f;
  }
  if (screenAspectRatio == self->owner->space->game->dimensions.aspectRatio) {
    sprite->visible = false;
  }
  if (screenAspectRatio < self->owner->space->game->dimensions.aspectRatio) {
    sprite->visible = true;
    trans->scale.x = (float)self->owner->space->game->innerWindow.width;
    trans->scale.y = (screenAspectRatio - self->owner->space->game->dimensions.aspectRatio) * (float)self->owner->space->game->dimensions.height / 2.0f;
    trans->translation.x = 0;
    if (data->id == 0)
      trans->translation.y = (float)self->owner->space->game->dimensions.height / 2.0f - trans->scale.y / 2.0f;
    else
      trans->translation.y = -(float)self->owner->space->game->dimensions.height / 2.0f + trans->scale.y / 2.0f;
  }
}

void comp_blackBarLogic_initialize(COMPONENT *self, void *event) {
  CDATA_BLACKBARLOGIC *data = (CDATA_BLACKBARLOGIC *)self->data;
  if (strcmp(self->owner->name, "blackbar1") == 0)
    data->id = 0;
  if (strcmp(self->owner->name, "blackbar2") == 0)
    data->id = 1;
}

void comp_blackBarLogic(COMPONENT *self) {
  CDATA_BLACKBARLOGIC data = { 0 };
  COMPONENT_INIT(self, COMP_BLACKBARLOGIC, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.initialize = comp_blackBarLogic_initialize;
  self->events.logicUpdate = comp_blackBarLogic_frameUpdate;
}