/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentscreen.h"
#include "studentscreenlogic.h"
#include "mousebox.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/generictext.h"
#include "../Nekoengine/spritetext.h"
#include "../NekoEngine/component.h"
#include "../NekoEngine/entity.h"
#include "../NekoEngine/sprite.h"
#include "schoollogic.h"

void comp_studentScreenLogic_logicUpdate(COMPONENT *self, void *event) {
  CDATA_STUDENTSCREEN *comData = (CDATA_STUDENTSCREEN *)self->data;


}

void comp_studentScreenLogic(COMPONENT *self) {
  VEC3 position = { 0, 0, 0 };
  VEC4 color = { 0, 0, 1, 1 };
  CDATA_STUDENTSCREEN data = { 0 };

  COMPONENT_INIT(self, COMP_STUDENTSCREENLOGIC, data);
  self->events.logicUpdate = comp_studentScreenLogic_logicUpdate;
}
