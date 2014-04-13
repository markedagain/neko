/******************************************************************************
Filename: mousebox.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_MOUSEBOX__
#define __COMP_MOUSEBOX__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/transform.h"
#include "../NekoEngine/sprite.h"
#include "../NekoEngine/game.h"

#define COMP_MOUSEBOX HASH("COMP_MOUSEBOX")

typedef struct {
  RECTANGLE box;
  RECTANGLE initBox;
  bool over;
  bool entered;
  bool exited;

  bool ghost;
  bool active;
  bool manual;

  struct {
    bool pressed;
    bool released;
    bool down;
  } left;

  struct {
    bool pressed;
    bool released;
    bool down;
  } right;

  bool pressHandle;
  bool releaseHandle;
} CDATA_MOUSEBOX;


void comp_mouseBox_logicUpdate(COMPONENT *self, void *event);
void comp_mouseBox(COMPONENT *self);
void comp_mouseBox_initialize(COMPONENT *self, void *event);
void set_box(COMPONENT *self, float left, float top, float right, float bot);
void set_box_sprite(COMPONENT *self);
void check_status(COMPONENT *self);
void comp_mouseBox_setInactive(CDATA_MOUSEBOX *mbox);


#endif
