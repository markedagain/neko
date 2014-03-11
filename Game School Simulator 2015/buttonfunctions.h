/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

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
void exit_onEntered(COMPONENT *self);
void exit_onPressed(COMPONENT *self);
void exit_onExit(COMPONENT *self);

#endif