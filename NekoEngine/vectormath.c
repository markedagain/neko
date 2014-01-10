/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#include "vectormath.h"
#include <math.h>

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

// function to multiply two matrixes together, and modify the matrix *mat2 points to
void matrix3_multiply(MATRIX3 *mat1, MATRIX3 *mat2) {
  // temp matrix to hold the resultant matrix
  MATRIX3 result;
  int i;

  // column 1 of resultant matrix
  result.m00 = mat1->m00 * mat2->m00 + mat1->m01 * mat2->m10 + mat1->m02 * mat2->m20;
  result.m01 = mat1->m00 * mat2->m01 + mat1->m01 * mat2->m11 + mat1->m02 * mat2->m21;
  result.m02 = mat1->m00 * mat2->m02 + mat1->m01 * mat2->m12 + mat1->m02 * mat2->m22;

  // column 2 of resultant matrix
  result.m10 = mat1->m10 * mat2->m00 + mat1->m11 * mat2->m10 + mat1->m12 * mat2->m20;
  result.m11 = mat1->m10 * mat2->m01 + mat1->m11 * mat2->m11 + mat1->m12 * mat2->m21;
  result.m12 = mat1->m10 * mat2->m02 + mat1->m11 * mat2->m12 + mat1->m12 * mat2->m22;

  // column 3 of resultant matrix
  result.m20 = mat1->m20 * mat2->m00 + mat1->m21 * mat2->m10 + mat1->m22 * mat2->m20;
  result.m21 = mat1->m20 * mat2->m01 + mat1->m21 * mat2->m11 + mat1->m22 * mat2->m21;
  result.m22 = mat1->m20 * mat2->m02 + mat1->m21 * mat2->m12 + mat1->m22 * mat2->m22;

  for (i = 0; i < 9; ++i)
    mat2->v[i] = result.v[i];  
}

void matrix3_identity(MATRIX3 *matrix) {
  matrix->m00 = 1;
  matrix->m01 = 0;
  matrix->m02 = 0;
  matrix->m10 = 0;
  matrix->m11 = 1;
  matrix->m12 = 0;
  matrix->m20 = 0;
  matrix->m21 = 0;
  matrix->m22 = 1;
}

void matrix3_rotate(MATRIX3 *matrix, float theta) {
  
  MATRIX3 rotateMatrix;
  
  rotateMatrix.m00 = cosf(theta);
  rotateMatrix.m01 = -sinf(theta);
  rotateMatrix.m02 = 0;
  rotateMatrix.m10 = sinf(theta);
  rotateMatrix.m11 = cosf(theta);
  rotateMatrix.m12 = 0;
  rotateMatrix.m20 = 0;
  rotateMatrix.m21 = 0;
  rotateMatrix.m22 = 1;

  matrix3_multiply(&rotateMatrix, matrix);
}

void matrix3_scale(MATRIX3 *matrix, VEC3 *scale) {
  
  MATRIX3 scaleMatrix;
  scaleMatrix.m00 = scale->x;
  scaleMatrix.m01 = 0;
  scaleMatrix.m02 = 0;
  scaleMatrix.m10 = 0;
  scaleMatrix.m11 = scale->y;
  scaleMatrix.m12 = 0;
  scaleMatrix.m10 = 0;
  scaleMatrix.m20 = 0;
  scaleMatrix.m21 = 0;
  scaleMatrix.m22 = 1;

  matrix3_multiply(&scaleMatrix, matrix);
}


void matrix3_translate(MATRIX3 *matrix, VEC3 *translation) {
  matrix->m02 += translation->x;
  matrix->m12 += translation->y;
}