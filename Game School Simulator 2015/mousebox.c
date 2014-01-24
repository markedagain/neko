/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "mousebox.h"

void comp_mouseBox_logicUpdate(COMPONENT *self, void *event) {
  check_hover(self);
}

void comp_mouseBox(COMPONENT *self) {
  CDATA_MOUSEBOX data = { 0 };
  COMPONENT_INIT(self, COMP_MOUSEBOX, data);
  component_depend(self, COMP_TRANSFORM);
  component_depend(self, COMP_SPRITE);
  self->events.logicUpdate = comp_mouseBox_logicUpdate;
  self->events.destroy = comp_mouseBox_destroy;
  self->events.initialize = comp_mouseBox_initialize;
}

void comp_mouseBox_initialize(COMPONENT *self, void *event) {
  set_box(self, -100.0f, 100.0f, 100.0f, -100.0f);
}

void comp_mouseBox_destroy(COMPONENT *self, void *event) {
}

void set_box(COMPONENT *self, float left, float top, float right, float bot) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;

  data->box.topLeft.x = left;
  data->box.topLeft.y = top;
  data->box.botRight.x = right;
  data->box.botRight.y = bot;
}

void check_hover(COMPONENT *self) {
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)self->data;
  POINT mousePos;
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  RECTANGLE box = data->box;
  float posX;
  float posY;

  space_mouseToWorld(self->owner->space, &input->mouse.position, &mousePos);
  
  posX = (float)mousePos.x;
  posY = (float)mousePos.y;

  if ((posX >= box.topLeft.x && posX <= box.botRight.x) && (posY <= box.topLeft.y && posY >= box.botRight.y))
    data->hover = true;
  else
    data->hover = false;
}

/******************************************************
  //the following code will print "butts" if the mouse is in the 'box' defined in mousebox and the lmb is down
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_MOUSEBOX *data = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  if ((data->hover == true) && (input->mouse.left == ISTATE_DOWN))
    printf("butts");
******************************************************/