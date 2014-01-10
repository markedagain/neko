/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EASINGS_H__
#define __EASINGS_H__

#include "neko.h"

typedef enum {
  LINEAR,
  QUAD_IN,
  QUAD_OUT,
  QUAD_INOUT,
  CUBIC_IN,
  CUBIC_OUT,
  CUBIC_INOUT,
  QUARTIC_IN,
  QUARTIC_OUT,
  QUARTIC_INOUT,
  QUINTIC_IN,
  QUINTIC_OUT,
  QUINTIC_INOUT,
  SINE_IN,
  SINE_OUT,
  SINE_INOUT,
  CIRCULAR_IN,
  CIRCULAR_OUT,
  CIRCULAR_INOUT,
  EXPONENTIAL_IN,
  EXPONENTIAL_OUT,
  EXPONENTIAL_INOUT,
  ELASTIC_IN,
  ELASTIC_OUT,
  ELASTIC_INOUT,
  BACK_IN,
  BACK_OUT,
  BACK_INOUT,
  BOUNCE_IN,
  BOUNCE_OUT,
  BOUNCE_INOUT
} easing;

NEKO_API float e_linear(float, float, float, float);
NEKO_API float e_quad_in(float, float, float, float);
NEKO_API float e_quad_out(float, float, float, float);
NEKO_API float e_quad_inout(float, float, float, float);
NEKO_API float e_cubic_in(float, float, float, float);
NEKO_API float e_cubic_out(float, float, float, float);
NEKO_API float e_cubic_inout(float, float, float, float);
NEKO_API float e_quartic_in(float, float, float, float);
NEKO_API float e_quartic_out(float, float, float, float);
NEKO_API float e_quartic_inout(float, float, float, float);
NEKO_API float e_quintic_in(float, float, float, float);
NEKO_API float e_quintic_out(float, float, float, float);
NEKO_API float e_quintic_inout(float, float, float, float);
NEKO_API float e_sine_in(float, float, float, float);
NEKO_API float e_sine_out(float, float, float, float);
NEKO_API float e_sine_inout(float, float, float, float);
NEKO_API float e_exponential_in(float, float, float, float);
NEKO_API float e_exponential_out(float, float, float, float);
NEKO_API float e_exponential_inout(float, float, float, float);
NEKO_API float e_circular_in(float, float, float, float);
NEKO_API float e_circular_out(float, float, float, float);
NEKO_API float e_circular_inout(float, float, float, float);

/*typedef int (* easing_function)(int, int);
easing_function easings[] = {
  e_linear,
  e_quad_in,
  e_quad_out,
  e_quad_inout,
  e_cubic_in,
  e_cubic_out,
  e_cubic_inout,
  e_quartic_in,
  e_quartic_out,
  e_quartic_inout,
  e_quintic_in,
  e_quintic_out,
  e_quintic_inout,
  e_sine_in,
  e_sine_out,
  e_sine_inout,
  e_back_in,
  e_back_out,
  e_back_inout,
  e_bounce_in,
  e_bounce_out,
  e_bounce_inout
}*/

#endif