/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_NEWSFEEDLOGIC__
#define __COMP_NEWSFEEDLOGIC__

#include "../NekoEngine/component.h"
#include "../NekoEngine/hash.h"
#include "newsfeed.h"

#define COMP_NEWSFEEDLOGIC HASH("COMP_NEWSFEEDLOGIC")

typedef enum {
  STINGS_WELCOME,
  STRINGS_ENROLL,
  STRINGS_DROP,
  STRINGS_GRAD,
  STRINGS_SEMESTER,
  STRINGS_YEAR,
  STRINGS_LAST
} STRINGS;

typedef struct cdata_newsfeedlogic_t {
  LIST *messages;
  ENTITY *lines[5];
  double fadeOutStartTime;
  double delayTime;
  bool locked;
} CDATA_NEWSFEEDLOGIC;

char *pushStrings[STRINGS_LAST];

void comp_newsfeedlogic_initialize(COMPONENT *self, void *event);
void comp_newsfeedlogic_logicUpdate(COMPONENT *self, void *event);
void comp_newsfeedlogic_destroy(COMPONENT *, void *);
void comp_newsfeedlogic_push(COMPONENT *ptr, char *string);
void comp_newsfeedlogic(COMPONENT *);

#endif
