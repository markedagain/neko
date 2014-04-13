/******************************************************************************
Filename: vectormath.h

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#ifndef __VECTORMATH_H__
#define __VECTORMATH_H__

#include "neko.h"

typedef struct vec2_t {
  float x;
  float y;
} VEC2;

typedef struct vec3_t {
  float x;
  float y;
  float z;
} VEC3;

typedef struct vec4_t {
  union {
    struct {
      float x, y, z, w;
    };
    struct {
      float r, g, b, a;
    };
    float v[4];
  };
} VEC4;

typedef struct matrix3_t {
  union {
    struct {
      float m00, m01, m02,
            m10, m11, m12,
            m20, m21, m22;
    };
    float m[3][3];
    float v[9];
  };
} MATRIX3;

typedef struct rect_t {
  VEC2 topLeft;
  VEC2 botRight;
} RECTANGLE;

NEKO_API void vec2_set(VEC2 *a, float x, float y);
NEKO_API void vec2_copy(VEC2 *destination, VEC2 *source);
NEKO_API void vec2_add(VEC2 *a, VEC2 *b, VEC2 *c);
NEKO_API void vec2_sub(VEC2 *a, VEC2 *b, VEC2 *c);
NEKO_API void vec2_mul(VEC2 *, float, VEC2 *);
NEKO_API void vec2_div(VEC2 *, float, VEC2 *);
NEKO_API float vec2_dot(VEC2 *a, VEC2 *b);
NEKO_API float vec2_angleBetween(VEC2 *a, VEC2 *b);
NEKO_API float vec2_magnitude(VEC2 *a);

NEKO_API void vec3_set(VEC3 *a, float x, float y, float z);
NEKO_API void vec3_copy(VEC3 *destination, VEC3 *source);
NEKO_API void vec3_add(VEC3 *, VEC3 *, VEC3 *);
NEKO_API void vec3_sub(VEC3 *, VEC3 *, VEC3 *);
NEKO_API void vec3_mul(VEC3 *, float, VEC3 *);
NEKO_API void vec3_div(VEC3 *, float, VEC3 *);
NEKO_API float vec3_dot(VEC3 *, VEC3 *);
NEKO_API void vec3_cross(VEC3 *, VEC3 *, VEC3 *);
NEKO_API float vec3_angleBetween(VEC3 *, VEC3 *);
NEKO_API float vec3_magnitude(VEC3 *);

NEKO_API void vec4_set(VEC4 *a, float x, float y, float z, float w);
NEKO_API void vec4_copy(VEC4 *destination, VEC4 *source);
NEKO_API void vec4_add(VEC4 *, VEC4 *, VEC4 *);
NEKO_API void vec4_sub(VEC4 *, VEC4 *, VEC4 *);
NEKO_API void vec4_mul(VEC4 *, float, VEC4 *);
NEKO_API void vec4_div(VEC4 *, float, VEC4 *);
NEKO_API long vec4_toColor(VEC4 *);

NEKO_API void matrix3_identity(MATRIX3 *);
NEKO_API void matrix3_translate(MATRIX3 *, VEC3 *);
NEKO_API void matrix3_scale(MATRIX3 *, VEC3 *);
NEKO_API void matrix3_rotate(MATRIX3 *, float);
NEKO_API void matrix3_multiply(MATRIX3 *, MATRIX3 *);
NEKO_API void matrix3_apply_to_vector(VEC3 *vector, MATRIX3 *matrix);

NEKO_API float angle_normalize(float angle);

#endif
