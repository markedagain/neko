/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_TIMEMANAGER__
#define __COMP_TIMEMANAGER__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_TIMEMANAGER HASH("COMP_TIMEMANAGER")

typedef struct cdata_timeManager_t {
  int secondsPerMonth;
  int speedMultiplier;
  BOOL paused;
  int months;
  int currentSemester;
  int previousYear;
  int currentYear;
  int frameCounter;
  int monthCounter;
  int semesterCounter;
  ENTITY *timeUI;
} CDATA_TIMEMANAGER;

char *month[12];
char *semester[2];

void comp_timeManager_logicUpdate(COMPONENT *, void *);
void comp_timeManager_pause(COMPONENT *ptr);
void comp_timeManager_fastForward(COMPONENT *ptr);
void comp_timeManager_slowDown(COMPONENT *ptr);
void comp_timeManager(COMPONENT *);

#endif