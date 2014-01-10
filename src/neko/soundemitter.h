/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __SOUNDEMITTER_H__
#define __SOUNDEMITTER_H__

#include "component.h"
#include "hash.h"
#include "../alpha/AEEngine.h"
#include "util.h"

#define COMP_SOUNDEMITTER HASH("COMP_SOUNDEMITTER")

typedef struct cdata_soundEmitter_t {
  void *cue;
  bool autoStart;
  float pitch;
  float volume;
} CDATA_SOUNDEMITTER;

void comp_soundEmitter_initialize(COMPONENT *, void *);
void comp_soundEmitter_frameUpdate(COMPONENT *, void *);
void comp_soundEmitter_destroy(COMPONENT *, void *);

void comp_soundEmitter(COMPONENT *);

#endif