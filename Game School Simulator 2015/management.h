/******************************************************************************
Filename: management.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_MANAGEMENT__
#define __COMP_MANAGEMENT__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_MANAGEMENT HASH("COMP_MANAGEMENT")

typedef struct{
  char gpaBuffer[40];
  char tuitionBuffer[40];
  char costsBuffer[40];
  char studentPopBuffer[40];
  char studentIncBuffer[40];
  char reputationBuffer[40];
  char incomeBuffer[40];
  char graduateBuffer[10];
  char dropoutBuffer[10];
  int currStudentInc;
  int currUpkeep;
  int currTuition;
  int currStudentPop;
  int currReputation;
  int expectedIncome;
  int numDropouts;
  int numGraduates;
  float currMinGpa;
  bool closed;
  ENTITY *gpa;
  ENTITY *tuition;
  ENTITY *rep;
  ENTITY *repTitle;
  ENTITY *manageWindow;
  ENTITY *currMoney;
  ENTITY *currCosts;
  ENTITY *currIncome;
  ENTITY *studentPop;
  ENTITY *studentInc;
  ENTITY *income;
  ENTITY *grads;
  ENTITY *dropoutsText;
  ENTITY *hoverText;
  ENTITY *schoolName;

  bool triggered;
  bool alreadyActivated;
} CDATA_MANAGEMENT;

void comp_managementUpdate(COMPONENT *self, void *event);
void comp_management(COMPONENT *self);
void comp_managementDisplay(COMPONENT *self);
void comp_managementRemove(COMPONENT *self);


#endif
