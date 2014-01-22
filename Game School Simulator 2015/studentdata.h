/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTDATA_H__
#define __COMP_STUDENTDATA_H__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include <string.h>
#define COMP_STUDENTDATA HASH("COMP_STUDENTDATA")


typedef struct cdata_studentData_t {
  char *firstname;
  char *lastname;
  int techSkill;
  int artSkill;
  int designSkill;
  int motivation;
  int yearStarted;
} CDATA_STUDENTDATA;

void comp_studentData_logicUpdate(COMPONENT *, void *);
void comp_studentData(COMPONENT *);
#endif