/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "easing.h"
#include <math.h>

float e_linear(float t, float b, float c, float d) {
  return c * t / d + b;
}

float e_quad_in(float t, float b, float c, float d) {
  return c * (t /= d) * t * t * t + b;
}

float e_quad_out(float t, float b, float c, float d) {
  return - c * ((t = t / d - 1.0f) * t * t * t - 1.0f) + b;
}

float e_quad_inOut(float t, float b, float c, float d) {
  if ((t /= d / 2.0f) < 1)
    return c / 2.0f * t * t * t * t + b;
  return -c / 2.0f * ((t -= 2) * t * t * t - 2.0f) + b;
}

float e_cubic_in(float t, float b, float c, float d) {
  return c * (t /= d) * t * t + b;
}

float e_cubic_out(float t, float b, float c, float d) {
  return c * (( t = t / d - 1.0f) * t * t + 1.0f) + b;
}

float e_cubic_inOut(float t, float b, float c, float d){
  if ((t /= d / 2.0f) < 1.0f)
    return c / 2.0f * t * t * t + b;
  return c / 2.0f * ((t -= 2.0f) * t * t + 2.0f) + b;
}

float e_quartic_in(float t, float b, float c, float d) {
  return c * (t /= d) * t * t * t + b;
}

float e_quartic_out(float t, float b, float c, float d) {
  return -c * ((t = t / d - 1.0f) * t * t * t - 1.0f) + b;
}

float e_quartic_inOut(float t, float b, float c, float d) {
  if ((t /= d / 2.0f) < 1)
    return c / 2.0f * t * t * t * t + b;
  return - c / 2.0f * ((t -= 2.0f) * t * t * t - 2.0f) + b;
}

float e_quintic_in(float t, float b, float c, float d) {
  return c * (t /= d) * t * t * t * t + b;
}

float e_quintic_out(float t, float b, float c, float d) {
  return c * ((t = t / d - 1.0f) * t * t * t * t + 1.0f) + b;
}

float e_quintic_inOut(float t, float b, float c, float d) {
  if ((t /= d / 2.0f) < 1.0f)
    return c / 2.0f * t * t * t * t * t + b;
  return c / 2.0f * (( t -= 2.0f) * t * t * t * t + 2.0f) + b;
}

float e_sine_in(float t, float b, float c, float d) {
  return -c * cosf(t / d * ((float)M_PI / 2.0f)) + c + b;
}

float e_sine_out(float t, float b, float c, float d) {
  return c * sinf(t / d * ((float)M_PI / 2.0f)) + b;
}

float e_sine_inOut(float t, float b, float c, float d) {
  return -c / 2.0f * (cosf((float)M_PI * t / d) - 1.0f) + b;
}

float e_circular_in(float t, float b, float c, float d) {
  return -c * (sqrtf(1.0f - (t /= d) * t) - 1.0f) + b;
}

float e_circular_out(float t, float b, float c, float d) {
  return c * sqrtf(1.0f - (t = t / d - 1.0f) * t) + b;
}

float e_circular_inOut(float t, float b, float c, float d) {
  if ((t /= d / 2.0f) < 1.0f)
    return -c / 2.0f * (sqrtf(1.0f - t * t) - 1.0f) + b;
  return c / 2.0f * (sqrtf(1.0f - t * (t -= 2)) + 1.0f) + b;
}

float e_exponential_in(float t, float b, float c, float d) {
  return (t == 0) ? b : c * powf(2.0f, 10.0f * (t / d - 1.0f)) + b;
}

float e_exponential_out(float t, float b, float c, float d) {
  return (t == d) ? b + c : c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b;
}

float e_exponential_inOut(float t, float b, float c, float d) {
  if (t == 0)
    return b;
  if (t == d)
    return b + c;
  if ((t /= d / 2.0f) < 1.0f)
    return c / 2.0f * powf(2.0f, 10.0f * (t - 1.0f)) + b;
  return c / 2.0f * (-powf(2.0f, -10.0f * --t) + 2.0f) + b;
}

float e_elastic_in(float t, float b, float c, float d) {
  float p, a, s, postFix;
  if (t == 0)
    return b;
  if ((t /= d) == 1.0f)
    return b + c;
  p = d * 0.3f;
  a = c;
  s = p / 4.0f;
  postFix = a * powf(2.0f, 10.0f * (t -= 1.0f));
  return -(postFix * sinf((t * d - s) * (2.0f * M_PI) / p)) + b;
}

float e_elastic_out(float t, float b, float c, float d) {
  float p, a, s;
  if (t == 0)
    return b;
  if ((t /= d) == 1.0f)
    return b + c;
  p = d * 0.3f;
  a = c;
  s = p / 4.0f;
  return (a * powf(2.0f, -10.0f * t) * sinf((t * d - s) * (2.0f * M_PI) / p) + c + b);
}

float e_elastic_inOut(float t, float b, float c, float d) {
  float p, a, s, postFix;
  if (t == 0)
    return b;
  if ((t /= d / 2.0f) == 2.0f)
    return b + c;
  p = d * (0.3f * 1.5f);
  a = c;
  s = p / 4.0f;
  postFix;
  if (t < 1.0f) {
    postFix = a * powf(2.0f, 10.0f * (t -= 1.0f));
    return -0.5f * (postFix * sinf((t * d - s) * (2.0f * M_PI) / p)) + b;
  }
  postFix = a * powf(2.0f, -10.0f * (t -= 1.0f));
  return postFix * sinf((t * d - s) * (2.0f * M_PI) / p) * 0.5f + c + b;
}

float e_back_in(float t, float b, float c, float d) {
  float s = 1.70158f;
  float postFix = t /= d;
  return c * (postFix) * t * ((s + 1.0f) * t - s) + b;
}

float e_back_out(float t, float b, float c, float d) {
  float s = 1.70158f;
  return c * ((t = t / d - 1.0f) * t * ((s + 1.0f) * t + s) + 1.0f) + b;
}

float e_back_inOut(float t, float b, float c, float d) {
  float s = 1.70158f;
  float postFix;
  if ((t /= d / 2.0f) < 1.0f)
    return c / 2.0f * (t * t * (((s *= (1.525f)) + 1.0f) * t - s)) + b;
  postFix = t -= 2;
  return c / 2.0f * ((postFix) * t * (((s *= (1.525f)) + 1.0f) * t + s) + 2.0f) + b;
}

float e_bounce_in(float t, float b, float c, float d) {
  return c - e_bounce_out(d - t, 0.0f, c, d) + b;
}

float e_bounce_out(float t, float b, float c, float d) {
  float postFix;
  if ((t /= d) < (1.0f / 2.75f))
    return c * (7.5625f * t * t) + b;
  if (t < (2.0f / 2.75f)) {
    postFix = t -= (1.5f / 2.75f);
    return c * (7.5625f * postFix * t + 0.75f) + b;
  }
  if (t < (2.5f / 2.75f)) {
    postFix = t -= (2.25f / 2.75f);
    return c * (7.5625f * postFix * t + 0.9375f) + b;
  }
  postFix = t -= (2.625f / 2.75f);
  return c * (7.5625f * postFix * t + 0.984375f) + b;
}

float e_bounce_inOut(float t, float b, float c, float d) {
  if (t < d / 2.0f)
    return e_bounce_in(t * 2.0f, 0.0f, c, d) * 0.5f + b;
  return e_bounce_out(t * 2.0f - d, 0.0f, c, d) * 0.5f + c * 0.5f + b;
}