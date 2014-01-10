/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "playerLogic.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/transform.h"

void comp_playerLogic_logicUpdate(COMPONENT *self, void *event) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)event;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  /*if (AEInputCheckCurr(VK_UP))
      trans->translation.y += 3.0f;
    if (AEInputCheckCurr(VK_DOWN))
      trans->translation.y -= 3.0f;
    if (AEInputCheckCurr(VK_LEFT))
      trans->translation.x -= 3.0f;
    if (AEInputCheckCurr(VK_RIGHT))
      trans->translation.x += 3.0f;
    if (AEInputCheckCurr(VK_SPACE)) {*/
      trans->scale.x *= 1.01f;
      trans->scale.y *= 1.01f;
      trans->rotation += 0.01f;
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
}