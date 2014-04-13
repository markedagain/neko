/******************************************************************************
Filename: easing.h

Project Name: Game School Simulator 2015

Author: Adam Rezich

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __EASING_H__
#define __EASING_H__

#include "neko.h"

typedef enum {
  EASING_LINEAR,
  EASING_QUAD_IN,
  EASING_QUAD_OUT,
  EASING_QUAD_INOUT,
  EASING_CUBIC_IN,
  EASING_CUBIC_OUT,
  EASING_CUBIC_INOUT,
  EASING_QUARTIC_IN,
  EASING_QUARTIC_OUT,
  EASING_QUARTIC_INOUT,
  EASING_QUINTIC_IN,
  EASING_QUINTIC_OUT,
  EASING_QUINTIC_INOUT,
  EASING_SINE_IN,
  EASING_SINE_OUT,
  EASING_SINE_INOUT,
  EASING_EXPONENTIAL_IN,
  EASING_EXPONENTIAL_OUT,
  EASING_EXPONENTIAL_INOUT,
  EASING_CIRCULAR_IN,
  EASING_CIRCULAR_OUT,
  EASING_CIRCULAR_INOUT,
  EASING_ELASTIC_IN,
  EASING_ELASTIC_OUT,
  EASING_ELASTIC_INOUT,
  EASING_BACK_IN,
  EASING_BACK_OUT,
  EASING_BACK_INOUT,
  EASING_BOUNCE_IN,
  EASING_BOUNCE_OUT,
  EASING_BOUNCE_INOUT,
  EASING_LAST
} EASING;

/*

t = current time
b = start value
c = change in value (end value - beginning value)
d = duration

*/
NEKO_API float e_linear(float t, float b, float c, float d);
NEKO_API float e_quad_in(float t, float b, float c, float d);
NEKO_API float e_quad_out(float t, float b, float c, float d);
NEKO_API float e_quad_inOut(float t, float b, float c, float d);
NEKO_API float e_cubic_in(float t, float b, float c, float d);
NEKO_API float e_cubic_out(float t, float b, float c, float d);
NEKO_API float e_cubic_inOut(float t, float b, float c, float d);
NEKO_API float e_quartic_in(float t, float b, float c, float d);
NEKO_API float e_quartic_out(float t, float b, float c, float d);
NEKO_API float e_quartic_inOut(float t, float b, float c, float d);
NEKO_API float e_quintic_in(float t, float b, float c, float d);
NEKO_API float e_quintic_out(float t, float b, float c, float d);
NEKO_API float e_quintic_inOut(float t, float b, float c, float d);
NEKO_API float e_sine_in(float t, float b, float c, float d);
NEKO_API float e_sine_out(float t, float b, float c, float d);
NEKO_API float e_sine_inOut(float t, float b, float c, float d);
NEKO_API float e_exponential_in(float t, float b, float c, float d);
NEKO_API float e_exponential_out(float t, float b, float c, float d);
NEKO_API float e_exponential_inOut(float t, float b, float c, float d);
NEKO_API float e_circular_in(float t, float b, float c, float d);
NEKO_API float e_circular_out(float t, float b, float c, float d);
NEKO_API float e_circular_inOut(float t, float b, float c, float d);
NEKO_API float e_elastic_in(float t, float b, float c, float d);
NEKO_API float e_elastic_out(float t, float b, float c, float d);
NEKO_API float e_elastic_inOut(float t, float b, float c, float d);
NEKO_API float e_back_in(float t, float b, float c, float d);
NEKO_API float e_back_out(float t, float b, float c, float d);
NEKO_API float e_back_inOut(float t, float b, float c, float d);
NEKO_API float e_bounce_in(float t, float b, float c, float d);
NEKO_API float e_bounce_out(float t, float b, float c, float d);
NEKO_API float e_bounce_inOut(float t, float b, float c, float d);

typedef float (* EASING_FUNCTION)(float currentTime, float startValue, float endValue, float duration);

EASING_FUNCTION easings[EASING_LAST];

#endif
