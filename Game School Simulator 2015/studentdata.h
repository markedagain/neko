/******************************************************************************
Filename: studentdata.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_STUDENTDATA_H__
#define __COMP_STUDENTDATA_H__

typedef enum {
  GEN_MALE,
  GEN_FEMALE,
  } GENDER;

typedef enum {
  M_TECH,
  M_ART,
  M_DESIGN,
  } MAJOR;

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
  GENDER gender;
  MAJOR major;
  char *trait1;
  char *trait2;
  int techSkill;
  int artSkill;
  int designSkill;
  int head;
  int face;
  int hair;
  int body;
  int legs;
  float gpa;
  float techIncrease;
  float designIncrease;
  float artIncrease;
  float gradePoints;
  int motivation;
  int lifeModifier;
  int yearStarted;
  int semesterStarted;
  int tuition;
  int counter;
  bool graduated;
  LIST_NODE *listNodePtr;
} CDATA_STUDENTDATA;

void comp_studentData_initialize(COMPONENT *self, void *event);
void comp_studentData_logicUpdate(COMPONENT *, void *);
void comp_studentData(COMPONENT *self);
void generate_student(COMPONENT *self);
#endif