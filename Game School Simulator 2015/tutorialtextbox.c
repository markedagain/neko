/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "tutorialtextbox.h"
#include "tutorialtextboxlogic.h"
#include "transform.h"

void arch_tutorialTextBox(ENTITY *entity) {
  entity->id = ARCH_TUTORIALTEXTBOX;
  entity_connect(entity, comp_transform);
  entity_connect(entity, comp_tutorialTextBoxLogic);
}
