/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "sprite.h"
#include "../component.h"
#include "../entity.h"
#include "transform.h"

void comp_sprite(COMPONENT *self) {
  CDATA_SPRITE initData = {};
  COMPONENT_INIT(self, COMP_SPRITE, initData);
  component_depend(self, COMP_TRANSFORM);
}
