/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_STUDENTDATA_H__
#define __COMP_STUDENTDATA_H__

#ifndef __STUDENT_GENDER__
#define __STUDENT_GENDER__
typedef enum {
  Male,
  Female,
  } gender;
#endif

#ifndef __STUDENT_MAJOR__
#define __STUDENT_MAJOR__
typedef enum {
  Tech,
  Art,
  Design,
  } major;
#endif

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/game.h"
#include <string.h>
#define COMP_STUDENTDATA HASH("COMP_STUDENTDATA")

typedef struct cdata_studentData_t {
  struct {
    char *first;
    char *last;
  } name;
  gender gender;
  major major;
  int techSkill;
  int artSkill;
  int designSkill;
  int motivation;
  int yearStarted;
  int semesterStarted;
  int counter;
  bool graduated;
  LIST_NODE *listNodePtr;
} CDATA_STUDENTDATA;

void comp_studentData_initialize(COMPONENT *self, void *event);
void comp_studentData_logicUpdate(COMPONENT *, void *);
void comp_studentData(COMPONENT *self);
void generate_student(COMPONENT *self);
#endif