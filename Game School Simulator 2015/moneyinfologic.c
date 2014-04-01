/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "moneyinfologic.h"
#include "sprite.h"
#include "genericsprite.h"
#include "generictext.h"
#include "schoollogic.h"
#include "colors.h"
#include "sound.h"
#include "mousebox.h"

void comp_moneyInfoLogic_initialize(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  COMPONENT *box = (COMPONENT *)entity_getComponent(self->owner, COMP_MOUSEBOX);

  mbox->manual = true;
  set_box(box, -50, 50, 50, -50);
}

void comp_moneyInfoLogic_logicUpdate(COMPONENT *self, void *event) {
  INPUT_CONTAINER *input = &self->owner->space->game->input;
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);

  if(mbox->entered) {
    vec3_set(&trans->translation, trans->translation.x, trans->translation.y - 100, trans->translation.z);


  }

  if(mbox->exited) {
    vec3_set(&trans->translation, trans->translation.x, trans->translation.y + 100, trans->translation.z);
  }
}

void comp_moneyInfoLogic(COMPONENT *self) {
  CDATA_NEWSFEEDLOGIC data = {0};
  COMPONENT_INIT(self, COMP_MONEYINFOLOGIC, data);
  self->events.logicUpdate = comp_moneyInfoLogic_logicUpdate;
  self->events.initialize = comp_moneyInfoLogic_initialize;
}
