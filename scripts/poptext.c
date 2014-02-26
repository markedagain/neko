/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "poptext.h"
#include "poptextlogic.h"
#include "transform.h"

void arch_popText(ENTITY *entity) {
entity->id = ARCH_POPTEXT;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_popTextLogic);
}
