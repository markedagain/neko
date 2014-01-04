/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include <stdlib.h>
#include <string.h>
#include "transform.h"
#include "../component.h"
#include "../entity.h"

void comp_transform(COMPONENT *self) {
  CDATA_TRANSFORM initData = { { 0, 0, 0 }, { 1, 1, 1 }, 0 };
  COMPONENT_INIT(self, COMP_TRANSFORM, initData);
}
