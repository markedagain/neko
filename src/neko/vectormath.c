/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "vectormath.h"

VEC2 vec2_add(VEC2 *a, VEC2 *b) {
  VEC2 c = {0};
  c.x = a->x + b->x;
  c.y = a->y + b->y;
  return c;
}

VEC2 vec2_sub(VEC2 *a, VEC2 *b) {
  VEC2 c = {0};
  c.x = a->x - b->x;
  c.y = a->y - b->y;
  return c;
}

VEC2 vec2_mul(VEC2 *a, VEC2 *b) {
  VEC2 c = {0};
  c.x = a->x * b->x;
  c.y = a->y * b->y;
  return c;
}

VEC2 vec2_div(VEC2 *a, VEC2 *b) {
  VEC2 c = {0};
  c.x = a->x / b->x;
  c.y = a->y / b->y;
  return c;
}

float vec2_dot(VEC2 *a, VEC2 *b) {
  return a->x * b->x + a->y * b->y;
}

VEC3 vec3_add(VEC3 *a, VEC3 *b) {
  VEC3 c = {0};
  c.x = a->x + b->x;
  c.y = a->y + b->y;
  c.z = a->z + b->z;
  return c;
}

VEC3 vec3_sub(VEC3 *a, VEC3 *b) {
  VEC3 c = {0};
  c.x = a->x - b->x;
  c.y = a->y - b->y;
  c.z = a->z - b->z;
  return c;
}

VEC3 vec3_mul(VEC3 *a, VEC3 *b) {
  VEC3 c = {0};
  c.x = a->x * b->x;
  c.y = a->y * b->y;
  c.z = a->z * b->z;
  return c;
}

VEC3 vec3_div(VEC3 *a, VEC3 *b) {
  VEC3 c = {0};
  c.x = a->x / b->x;
  c.y = a->y / b->y;
  c.z = a->z / b->z;
  return c;
}

float vec3_dot(VEC3 *a, VEC3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

VEC3 vec3_cross(VEC3 *a, VEC3 *b) {
  VEC3 c = {0};
  c.x = a->y * b->z - a->z * b->y;
  c.y = -(b->z * a->x - b->x * a->z);
  c.z = a->x * b->y - a->y * b->x;
  return c;
}

VEC4 vec4_add(VEC4 *a, VEC4 *b) {
  VEC4 c = {0};
  c.x = a->x + b->x;
  c.y = a->y + b->y;
  c.z = a->z + b->z;
  c.w = a->w + b->w;
  return c;
}

VEC4 vec4_sub(VEC4 *a, VEC4 *b) {
  VEC4 c = {0};
  c.x = a->x - b->x;
  c.y = a->y - b->y;
  c.z = a->z - b->z;
  c.w = a->w - b->w;
  return c;
}

VEC4 vec4_mul(VEC4 *a, VEC4 *b) {
  VEC4 c = {0};
  c.x = a->x * b->x;
  c.y = a->y * b->y;
  c.z = a->z * b->z;
  c.w = a->w * b->w;
  return c;
}

VEC4 vec4_div(VEC4 *a, VEC4 *b) {
  VEC4 c = {0};
  c.x = a->x / b->x;
  c.y = a->y / b->y;
  c.z = a->z / b->z;
  c.w = a->w / b->w;
  return c;
}