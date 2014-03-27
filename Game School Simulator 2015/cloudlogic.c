/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "cloudLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/transform.h"

// fix all mboxes to handle things
void comp_cloudLogic_logicUpdate(COMPONENT *self, void *event) {

}


void comp_cloudLogic(COMPONENT *self) {
  CDATA_CLOUDLOGIC data = { 0 };
  data.speed = 1;

  COMPONENT_INIT(self, COMP_CLOUDLOGIC, data);
  self->events.logicUpdate = comp_cloudLogic_logicUpdate;
}
