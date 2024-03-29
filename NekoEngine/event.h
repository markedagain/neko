/******************************************************************************
Filename: event.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content � 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __EVENT_H__
#define __EVENT_H__

#include "neko.h"

typedef struct entity_t ENTITY;
typedef struct component_t COMPONENT;

typedef enum eventType_t {
  EV_INITIALIZE,
  EV_DESTROY,
  EV_LOGICUPDATE,
  EV_FRAMEUPDATE,
  EV_DRAW,
  EV_LAST
} EVENT_TYPE;

typedef struct edata_update_t {
  double dt;
  double elapsedTime;
} EDATA_UPDATE;

typedef struct eventcontainer_t {
  union {
    struct {
      void (*initialize)(COMPONENT *, void *);
      void (*destroy)(COMPONENT *, void *);
      void (*logicUpdate)(COMPONENT *, void *);
      void (*frameUpdate)(COMPONENT *, void *);
      void (*draw)(COMPONENT *, void *);
    };
    void (*ids[EV_LAST])(COMPONENT *, void *);
  };
} EVENTCONTAINER;

void eventcontainer_initialize(EVENTCONTAINER *);

#endif
