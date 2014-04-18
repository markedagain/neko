/******************************************************************************
Filename: roomlogic.h

Project Name: Game School Simulator 2015

Author: Eduardo Gorinstein

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __COMP_ROOMLOGIC__
#define __COMP_ROOMLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"

#define COMP_ROOMLOGIC HASH("COMP_ROOMLOGIC")

typedef enum {
  ROOMTYPE_LOBBY,
  ROOMTYPE_CLASS,
  ROOMTYPE_LIBRARY,
  ROOMTYPE_TEAMSPACE,
  ROOMTYPE_CAFETERIA,
  ROOMTYPE_STORE,
  ROOMTYPE_OFFICES,
  ROOMTYPE_AUDITORIUM,
  ROOMTYPE_TUTORING,
  ROOMTYPE_IT,
  ROOMTYPE_RECREATION,
  ROOMTYPE_FIGURE,
  ROOMTYPE_POTTERY
} ROOM_TYPE;

typedef struct cdata_roomlogic_t {
  ROOM_TYPE type;
  int cost;
  int upgradeCost;
  int upkeep;
  int size;
  int level;
  int techBonus;
  int designBonus;
  int artBonus;
  int motivationBonus;
  int repBonus;
  int frameCounter;
} CDATA_ROOMLOGIC;

void comp_roomLogic_frameUpdate(COMPONENT *, void *);
void comp_roomLogic_createRoom(COMPONENT *self);
void comp_roomLogic_upgradeRoom(COMPONENT *self);
void comp_roomLogic(COMPONENT *);
int comp_roomLogic_getRoomCost(ROOM_TYPE type);
int comp_roomLogic_getRoomUpgradeCost(ROOM_TYPE type);

#endif