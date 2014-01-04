/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __COMP_TRANSFORM_H__
#define __COMP_TRANSFORM_H__

#include "../component.h"
#include "../vectormath.h"

extern int COMP_TRANSFORM;

typedef struct cdata_transform_t {
  VEC3 translation;
  VEC3 scale;
  float rotation;
} CDATA_TRANSFORM;

void comp_transform(COMPONENT *);

#endif
