/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cursorlogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include <math.h>

void comp_cursorLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  POINT mousePos;
  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  trans->translation.x = mousePos.x;
  trans->translation.y = mousePos.y;
  snap_sprite(self, snaps, 2, 100);
}

void comp_cursorLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_CURSORLOGIC);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_cursorLogic_logicUpdate;
}

// makes the sprite snap to all positions in an array of VEC3s (snaps)
void snap_sprite(COMPONENT *self, VEC3 *snaps, int size, float distance) {
  CDATA_TRANSFORM *transformData = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  int i;
  float diffX, diffY;

  for (i = 0; i < size; i++){
    diffX = snaps[i].x - transformData->translation.x;
    diffY = snaps[i].y - transformData->translation.y;

    if((float)(sqrt(diffX * diffX + diffY * diffY)) < distance) {
      transformData->translation.x = snaps[i].x;
      transformData->translation.y = snaps[i].y;
    }
  }

}