/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "studentmanager.h"
#include "studentmanagerlogic.h"

void arch_studentManager(ENTITY *entity) {
  entity->id = ARCH_STUDENTMANAGER;
  entity_connect(entity, comp_studentManagerLogic);
}
