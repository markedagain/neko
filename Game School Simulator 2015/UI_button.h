/******************************************************************************
Filename: UI_button.h

Project Name: Game School Simulator 2015

Author: Samuel Valdez

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_UI_BUTTON__
#define __COMP_UI_BUTTON__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "roomlogic.h"
#include "actionlist.h"

#define COMP_UI_BUTTON HASH("COMP_UI_BUTTON")

typedef enum { // DO NOT MOVE THE LOBBY - POTTERY BUTTONS, THEY NEED TO BE ON TOP IN THIS ORDER
  BUTTON_BUILDLOBBY,
  BUTTON_BUILDCLASS,
  BUTTON_BUILDLIBRARY,
  BUTTON_BUILDTEAMSPACE,
  BUTTON_BUILDCAFETERIA,
  BUTTON_BUILDSTORE,
  BUTTON_BUILDOFFICES,
  BUTTON_BUILDAUDITORIUM,
  BUTTON_BUILDTUTORING,
  BUTTON_BUILDIT,
  BUTTON_BUILDRECREATION,
  BUTTON_BUILDFIGURE,
  BUTTON_BUILDPOTTERY,
  BUTTON_BUILD,
  BUTTON_CANCEL,
  BUTTON_GPA_INCREMENT,
  BUTTON_GPA_DECREMENT,
  BUTTON_TUITION_INCREMENT,
  BUTTON_TUITION_DECREMENT,
  BUTTON_ROOM_UPGRADE,
  BUTTON_SPEED,
  BUTTON_PAUSE,
  BUTTON_DEFAULT,
} BUTTON_TYPE;

typedef struct{
  ENTITY *ent1;
  ENTITY *ent2;
  ENTITY *ent3;
  BUTTON_TYPE type;
  ALIST actions;
  float startY;
  float startZoom;
  float origin;
  bool clickable;
  bool unlocked;
  bool firstBuildClick;
  bool lobbyBuilt;
  bool firstLobby;
  ENTITY *text;
} CDATA_UI_BUTTON;

void UI_buttonUpdate(COMPONENT *self, void *event);
void comp_UI_button(COMPONENT *self);
void __UI_button_cancelBuildMode(COMPONENT *self);
void UI_button_createGhostRooms(COMPONENT *self, ROOM_TYPE toBuild);
void UI_button_deleteList(LIST *buildSpaces);
void UI_button_createRoomButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name);
void UI_button_destroyGhostRooms(COMPONENT *self);
void comp_UI_button_panDown(COMPONENT *self);
void comp_UI_button_panUp(COMPONENT *self);
void UI_button_createManagementButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name);
void UI_button_createUpgradeButton(COMPONENT *self, BUTTON_TYPE type, VEC3 *position, VEC4 *color, char *name);
void comp_UI_destroy(COMPONENT *self, void *event);
void UI_button_updateBuildButtons(SPACE *ui);
void comp_ui_button_hoverPop(COMPONENT *self);
void UI_button_updateUpgradeButton(SPACE *ui);
void comp_UI_button_cancelBuildMode(COMPONENT *buildButton);
void comp_UI_button_enterBuildMode(COMPONENT *buildButton);
void comp_UI_button_toggleBuildMode(COMPONENT *buildButton);

#endif
