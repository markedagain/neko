/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "../NekoEngine/component.h"
#include "student.h"
#include "studentdata.h"

void arch_student(ENTITY *entity) {
  entity->id = ARCH_STUDENT;

  entity_connect(entity, comp_studentData);
}