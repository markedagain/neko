/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __VECTORMATH_H__
#define __VECTORMATH_H__

typedef struct vec2_t {
  float x;
  float y;
} VEC2;

typedef struct vec3_t {
  float x;
  float y;
  float z;
} VEC3;

VEC2 vec2_add(VEC2 *, VEC2 *);
VEC2 vec2_sub(VEC2 *, VEC2 *);
VEC2 vec2_mul(VEC2 *, VEC2 *);
VEC2 vec2_div(VEC2 *, VEC2 *);
float vec2_dot(VEC2 *, VEC2 *);

VEC3 vec3_add(VEC3 *, VEC3 *);
VEC3 vec3_sub(VEC3 *, VEC3 *);
VEC3 vec3_mul(VEC3 *, VEC3 *);
VEC3 vec3_div(VEC3 *, VEC3 *);
float vec3_dot(VEC3 *, VEC3 *);
VEC3 vec3_cross(VEC3 *, VEC3 *);

#endif
