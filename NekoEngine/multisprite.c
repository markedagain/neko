/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "multisprite.h"
#include "sprite.h"

void comp_multiSprite(COMPONENT *self) {
  CDATA_MULTISPRITE data = { 0 };
  data.entities = list_create();
  COMPONENT_INIT(self, COMP_MULTISPRITE, data);
  component_depend(self, COMP_TRANSFORM);
}
