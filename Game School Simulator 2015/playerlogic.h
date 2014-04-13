/******************************************************************************
Filename: playerlogic.h

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_PLAYERLOGIC_H__
#define __COMP_PLAYERLOGIC_H__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "../NekoEngine/vectormath.h"

#define COMP_PLAYERLOGIC HASH("COMP_PLAYERLOGIC")

typedef enum {
  GM_DEFAULT = 0,
  GM_BUILD,
  GM_LOSE,
  GM_WIN,
  GM_PLAY,
  GM_PAUSE
} GMODE;


typedef struct {
  bool dragging;
  POINT dragOrigin;
  float zoomVelocity;
  float yLock;
  bool yPan;
  GMODE currentMode;
  bool lobbyBuilt;
  bool lobbyClicked;
  bool classroomBuilt;
  int lastSong;
  float nextSongTime;
} CDATA_PLAYERLOGIC;

void comp_playerLogic_initialize(COMPONENT *self, void *event);
void comp_playerLogic_logicUpdate(COMPONENT *, void *);
void comp_playerLogic_frameUpdate(COMPONENT *, void *);
void comp_playerLogic(COMPONENT *);
void pan(COMPONENT *self, float x, float y, POINT *outPoint);
void playerLogic_zoom(COMPONENT *playerLogic, float zoomAmt);
void playerLogic_pan(COMPONENT *playerLogic, float x, float y, POINT *outPoint);
void playerLogic_setZoom(COMPONENT *playerLogic, float newZoom);
void playerLogic_setCamVerticalPos(COMPONENT *playerLogic, float newY);

#endif