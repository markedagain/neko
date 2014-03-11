/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "custombuttonlogic.h"
#include "mousebox.h"

void comp_customButtonLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;

  if (mbox->entered)
    if (data->onEntered)
      data->onEntered(self);

  if (mbox->over)
    if (data->onOver)
      data->onOver(self);
  
  if (mbox->exited)
    if (data->onExit)
      data->onExit(self);

  if (mbox->left.pressed)
    if (data->onPressed)
      data->onPressed(self);
}

void comp_customButtonLogic(COMPONENT *self) {
  CDATA_CUSTOMBUTTON data = { 0 };
  data.sprite.color.r = 1.0f;
  data.sprite.color.g = 1.0f;
  data.sprite.color.b = 1.0f;
  data.sprite.color.a = 1.0f;
  al_init(&data.actions);
  COMPONENT_INIT(self, COMP_CUSTOMBUTTONLOGIC, data);
  self->events.logicUpdate = comp_customButtonLogic_logicUpdate;
  self->events.destroy = comp_customButtonLogic_destroy;
}

void comp_customButtonLogic_destroy(COMPONENT *self, void *event) {
  CDATA_CUSTOMBUTTON *data = (CDATA_CUSTOMBUTTON *)self->data;

  al_destroy(&data->actions);

  if (data->destroy)
    data->destroy(self);
}
