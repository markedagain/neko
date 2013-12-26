/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EVENT_H__
#define __EVENT_H__

typedef enum eventType_t {
  EV_NONE,
  EV_INITIALIZE,
  EV_DESTROY,
  EV_LOGICUPDATE_BEFORE,
  EV_LOGICUPDATE,
  EV_LOGICUPDATE_AFTER,
  EV_FRAMEUPDATE_BEFORE,
  EV_FRAMEUPDATE,
  EV_FRAMEUPDATE_AFTER,
  EV_COUNT
} EVENT_TYPE;

typedef struct updateEvent_t {
  float dt;
  float elapsedTime;
} EVENT_UPDATE;

typedef struct event_t {

} EVENT;

#endif
