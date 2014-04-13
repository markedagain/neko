/******************************************************************************
Filename: studentactorlogic.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_STUDENTACTORLOGIC__
#define __COMP_STUDENTACTORLOGIC__

#include "entity.h"
#include "hash.h"

#define COMP_STUDENTACTORLOGIC HASH("COMP_STUDENTACTORLOGIC")

typedef enum {
  OS_LEFT,
  OS_RIGHT,
  OS_IDLE,
  OS_FADEIN,
  OS_WALKTODOOR,
  OS_FADEOUT,
  IS_ENTER,
  IS_UPDATE,
  IS_EXIT
} STUDENT_STATE;

typedef enum {
  AF_IDLE,
  AF_WALK1,
  AF_WALK2
} ANIMATION_FRAME;

typedef struct {
  int ID;
  float stateTimer;
  float stateTime;
  float lifeTimer;
  float lifetime;
  float animationTimer;
  bool setSprite;
  float velocity;
  float roomSize;
  float origin;
  bool fadeIn;
  bool fadeOut;
  bool triggered;
  ENTITY *studentPtr;
  ENTITY *legsPointer;
  char legs[30];
  char walk1[30];
  char walk2[30];
  int currentFrame;
  char head[30];
  char face[30];
  char body[30];
  char hair[30];
  bool zoomedOut;
  STUDENT_STATE outerState;
  STUDENT_STATE innerState;
} CDATA_STUDENTACTOR;


void comp_studentActorLogic_logicUpdate(COMPONENT *self, void *event);
void comp_studentActorLogic(COMPONENT *self);
void comp_studentActorLogic_initialize(COMPONENT *self, void *event);
void comp_studentActorLogic_flipSprite(COMPONENT *self);
void comp_studentActorLogic_createPopText(COMPONENT *self, char *text);
void comp_studentActorLogic_updateState(COMPONENT *self);
void comp_studentActorLogic_flipText(ENTITY *text);
void __studentActorLogic_setLegs(COMPONENT *self, ANIMATION_FRAME frame);

#endif
