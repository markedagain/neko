/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "backgroundlogic.h"
#include "mousebox.h"
#include "playerlogic.h"

void comp_backgroundLogic_frameUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  if (mbox->left.down && !input->mouse.handled[MBUTTON_LEFT]) {
    ENTITY *player = space_getEntity(game_getSpace(self->owner->space->game, "ui"), "player");
    CDATA_PLAYERLOGIC *playerData = (CDATA_PLAYERLOGIC *)entity_getComponentData(player, COMP_PLAYERLOGIC);
    playerData->dragging = true;
    input_lockMouse(input);
    playerData->dragOrigin.x = input->mouse.position.x;
    playerData->dragOrigin.y = input->mouse.position.y;
    input->mouse.handled[MBUTTON_LEFT] = true;

  }
}

void comp_backgroundLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_BACKGROUNDLOGIC);
  component_depend(self, COMP_MOUSEBOX);
  self->events.frameUpdate = comp_backgroundLogic_frameUpdate;
}