/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EVENT_H__
#define __EVENT_H__

typedef struct entity_t ENTITY;
typedef struct component_t COMPONENT;

typedef enum eventType_t {
  EV_INITIALIZE,
  EV_DESTROY,
  EV_LOGICUPDATE,
  EV_FRAMEUPDATE,
  EV_LAST
} EVENT_TYPE;

typedef struct edata_update_t {
  float dt;
  float elapsedTime;
} EDATA_UPDATE;

typedef struct eventcontainer_t {
  union {
    struct {
      void (*initialize)(COMPONENT *);
      void (*destroy)(COMPONENT *);
      void (*logicUpdate)(COMPONENT *, EDATA_UPDATE *);
      void (*frameUpdate)(COMPONENT *, EDATA_UPDATE *);
    };
    void *ids[EV_LAST];
  };
} EVENTCONTAINER;

typedef void (*EVFN_GENERIC)(void);
typedef void (*EVFN_UPDATE)(COMPONENT *, EDATA_UPDATE *);

void eventcontainer_initialize(EVENTCONTAINER *);

#endif
