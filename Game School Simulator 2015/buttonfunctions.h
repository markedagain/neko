/******************************************************************************
Filename: buttonfunctions.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __ARCH_BUTTONFUNCTIONS__
#define __ARCH_BUTTONFUNCTIONS__

#include "entity.h"
#include "hash.h"
#include "generictext.h"

void newGame_onEntered(COMPONENT *self);
void newGame_onPressed(COMPONENT *self);
void newGame_onExit(COMPONENT *self);
void options_onEntered(COMPONENT *self);
void options_onPressed(COMPONENT *self);
void options_onExit(COMPONENT *self);
void credits_onEntered(COMPONENT *self);
void credits_onPressed(COMPONENT *self);
void credits_onExit(COMPONENT *self);
void fullScreen_onEntered(COMPONENT *self);
void fullScreen_onPressed(COMPONENT *self);
void fullScreen_onExit(COMPONENT *self);
void tutorial_onEntered(COMPONENT *self);
void tutorial_onPressed(COMPONENT *self);
void tutorial_onExit(COMPONENT *self);
void exit_onEntered(COMPONENT *self);
void exit_onPressed(COMPONENT *self);
void exit_onExit(COMPONENT *self);
void increaseGPA_onEntered(COMPONENT *self);
void increaseGPA_onPressed(COMPONENT *self);
void increaseGPA_onExit(COMPONENT *self);
void decreaseGPA_onEntered(COMPONENT *self);
void decreaseGPA_onPressed(COMPONENT *self);
void decreaseGPA_onExit(COMPONENT *self);
void increaseTuition_onEntered(COMPONENT *self);
void increaseTuition_onPressed(COMPONENT *self);
void increaseTuition_onExit(COMPONENT *self);
void decreaseTuition_onEntered(COMPONENT *self);
void decreaseTuition_onPressed(COMPONENT *self);
void decreaseTuition_onExit(COMPONENT *self);
void pause_onEntered(COMPONENT *self);
void pause_onPressed(COMPONENT *self);
void pause_onExit(COMPONENT *self);
void empty_onPressed(COMPONENT *self);

#endif