#include "roomactorlogic.h"
#include "mousebox.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/sprite.h"
#include <math.h>


void comp_roomActorLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_MOUSEBOX *mbox = (CDATA_MOUSEBOX *)entity_getComponentData(self->owner, COMP_MOUSEBOX);
  CDATA_SPRITE *sprite = (CDATA_SPRITE *)entity_getComponentData(self->owner, COMP_SPRITE);


  /*if (mbox->left.down) {
    //sprite->color.r = min(sprite->color.r + 0.05f, 1);
    sprite->color.b = max(sprite->color.b - 0.05f, 0);
    sprite->color.g = max(sprite->color.g - 0.05f, 0);
  }*/
  if (mbox->left.pressed) {
    sprite->color.b = 0.0f;
    sprite->color.g = 0.0f;
    sprite->color.r = 0.0f;
  }
  else if (mbox->left.released) {
    sprite->color.b = 0.0f;
    sprite->color.g = 1.0f;
    sprite->color.r = 0.0f;
  }
  else {
    sprite->color.b = 1.0f;
    sprite->color.g = 1.0f;
    sprite->color.r = 1.0f;
  }
}

void comp_roomActorLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_ROOMACTORLOGIC);
  component_depend(self, COMP_MOUSEBOX);
  self->events.logicUpdate = comp_roomActorLogic_logicUpdate;
}