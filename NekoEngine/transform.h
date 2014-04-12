/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_TRANSFORM_H__
#define __COMP_TRANSFORM_H__

#include "neko.h"
#include "component.h"
#include "vectormath.h"
#include "hash.h"
#include "event.h"

#define COMP_TRANSFORM HASH("COMP_TRANSFORM")

typedef struct cdata_transform_t {
  VEC3 translation;
  VEC3 scale;
  float rotation;
  struct { // in better languages this would be getters/setters
    VEC3 translation;
    VEC3 scale;
    float rotation;
  } world;
} CDATA_TRANSFORM;

void comp_transform_frameUpdate(COMPONENT *, void *);
void comp_transform_destroy(COMPONENT *, void *);

NEKO_API void comp_transform(COMPONENT *);

#endif
