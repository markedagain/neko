/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EVENT_H__
#define __EVENT_H__

typedef struct entity_t ENTITY;
typedef struct component_t COMPONENT;

typedef enum eventType_t {
  EV_NONE,
  EV_INITIALIZE,
  EV_DESTROY,
  EV_LOGICUPDATE,
  EV_FRAMEUPDATE,
  EV_COUNT
} EVENT_TYPE;

typedef struct edata_update_t {
  float dt;
  float elapsedTime;
} EDATA_UPDATE;

typedef struct eventcontainer_t {
  void (*initialize)(COMPONENT *);
  void (*destroy)(COMPONENT *);
  void (*logicUpdate)(COMPONENT *, EDATA_UPDATE *);
  void (*frameUpdate)(COMPONENT *, EDATA_UPDATE *);
} EVENTCONTAINER;

void eventcontainer_initialize(EVENTCONTAINER *);

#endif
