/******************************************************************************
Filename: student.c

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "../NekoEngine/component.h"
#include "student.h"
#include "studentdata.h"

void arch_student(ENTITY *entity) {
  entity->id = ARCH_STUDENT;

  entity_connect(entity, comp_studentData);
}