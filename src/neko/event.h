/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EVENT_H__
#define __EVENT_H__

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
  void (*initialize)(void);
  void (*destroy)(void);
  void (*logicUpdate)(EDATA_UPDATE *);
  void (*frameUpdate)(EDATA_UPDATE *);
} EVENTCONTAINER;

void eventcontainer_initialize(EVENTCONTAINER *);

#endif
