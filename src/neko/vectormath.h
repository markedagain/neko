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

VEC4 vec4_add(VEC4 *, VEC4 *);
VEC4 vec4_sub(VEC4 *, VEC4 *);
VEC4 vec4_mul(VEC4 *, VEC4 *);
VEC4 vec4_div(VEC4 *, VEC4 *);

void matrix3_identity(MATRIX3 *);
void matrix3_translate(MATRIX3 *, VEC3 *);
void matrix3_scale(MATRIX3 *, VEC3 *);
void matrix3_rotate(MATRIX3 *, float);
void matrix3_multiply(MATRIX3 *, MATRIX3 *);

#endif
