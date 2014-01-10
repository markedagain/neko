/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "playerLogic.h"
#include "../../neko/component.h"
#include "../../neko/entity.h"
#include "../../neko/components/transform.h"
#include "../../alpha/AEEngine.h"

void comp_playerLogic_logicUpdate(COMPONENT *self, void *data) {
  EDATA_UPDATE *updateEvent = (EDATA_UPDATE *)data;
  CDATA_TRANSFORM *trans = (CDATA_TRANSFORM *)entity_getComponentData(self->owner, COMP_TRANSFORM);
  if (AEInputCheckCurr(VK_UP))
			trans->translation.y += 3.0f;
		else
		if (AEInputCheckCurr(VK_DOWN))
			trans->translation.y -= 3.0f;

		if (AEInputCheckCurr(VK_LEFT))
			trans->translation.x -= 3.0f;
		else
		if (AEInputCheckCurr(VK_RIGHT))
			trans->translation.x += 3.0f;
}

void comp_playerLogic(COMPONENT *self) {
  COMPONENT_INIT_NULL(self, COMP_PLAYERLOGIC);
  component_depend(self, COMP_TRANSFORM);
  self->events.logicUpdate = comp_playerLogic_logicUpdate;
}