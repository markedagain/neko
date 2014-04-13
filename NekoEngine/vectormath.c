/******************************************************************************
Filename: vectormath.c

Project Name: Game School Simulator 2015

Author: Tai Der Hui

All content © 2014 DigiPen (USA) Corporation, all rights reserved.

******************************************************************************/


#include "vectormath.h"
#include <math.h>

void vec2_set(VEC2 *a, float x, float y) {
  a->x = x;
  a->y = y;
}

void vec2_copy(VEC2 *a, VEC2 *b) {
  a->x = b->x;
  a->y = b->y;
}

void vec2_add(VEC2 *a, VEC2 *b, VEC2 *c) {
  a->x = b->x + c->x;
  a->y = b->y + c->y;
}

void vec2_sub(VEC2 *a, VEC2 *b, VEC2 *c) {
  a->x = b->x - c->x;
  a->y = b->y - c->y;
}

void vec2_mul(VEC2 *a, float scalar, VEC2 *b) {
  a->x = scalar * b->x;
  a->y = scalar * b->y;
}

void vec2_div(VEC2 *a, float diviser, VEC2 *b) {
  a->x = b->x / diviser;
  a->y = b->y / diviser;
}

float vec2_dot(VEC2 *a, VEC2 *b) {
  return a->x * b->x + a->y * b->y;
}

float vec2_angleBetween(VEC2 *a, VEC2 *b) {
  float dotProduct = vec2_dot(a, b);
  float totalMagnitude = vec2_magnitude(a) * vec2_magnitude(b);
  return (acosf(dotProduct / totalMagnitude));
}

float vec2_magnitude(VEC2 *a) {
  return (float)sqrt(a->x * a->x + a->y * a->y);
}

void vec3_set(VEC3 *a, float x, float y, float z) {
  a->x = x;
  a->y = y;
  a->z = z;
}

void vec3_copy(VEC3 *a, VEC3 *b) {
  a->x = b->x;
  a->y = b->y;
  a->z = b->z;
}


void vec3_add(VEC3 *a, VEC3 *b, VEC3 *c) {
  a->x = b->x + c->x;
  a->y = b->y + c->y;
  a->z = b->z + c->z;
}

void vec3_sub(VEC3 *a, VEC3 *b, VEC3 *c) {
  a->x = b->x - c->x;
  a->y = b->y - c->y;
  a->z = b->z - c->z;
}

void vec3_mul(VEC3 *a, float scalar, VEC3 *b) {
  a->x = scalar * b->x;
  a->y = scalar * b->y;
  a->z = scalar * b->z;
}

void vec3_div(VEC3 *a, float divisor, VEC3 *b) {
  a->x = b->x / divisor;
  a->y = b->y / divisor;
  a->z = b->z / divisor;
}

float vec3_dot(VEC3 *a, VEC3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vec3_cross(VEC3 *a, VEC3 *b, VEC3 *c) {
  a->x = b->y * c->z - b->z * c->y;
  a->y = -(c->z * b->x -c->x * b->z);
  a->z = b->x * c->y - b->y * c->x;
}

float vec3_angleBetween(VEC3 *a, VEC3 *b) {
  float dotProduct = vec3_dot(a, b);
  float totalMagnitude = vec3_magnitude(a) * vec3_magnitude(b);
  return (acosf(dotProduct / totalMagnitude));
}

float vec3_magnitude(VEC3 *a) {
  return (float)sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
}

void vec4_set(VEC4 *a, float x, float y, float z, float w) {
  a->x = x;
  a->y = y;
  a->z = z;
  a->w = w;
}

void vec4_copy(VEC4 *a, VEC4 *b) {
  a->x = b->x;
  a->y = b->y;
  a->z = b->z;
  a->w = b->w;
}

void vec4_add(VEC4 *a, VEC4 *b, VEC4 *c) {
  a->x = b->x + c->x;
  a->y = b->y + c->y;
  a->z = b->z + c->z;
  a->w = b->w + c->w;
}

void vec4_sub(VEC4 *a, VEC4 *b, VEC4 *c) {
  a->x = b->x - c->x;
  a->y = b->y - c->y;
  a->z = b->z - c->z;
  a->w = b->w - c->w;
}

void vec4_mul(VEC4 *a, float scalar, VEC4 *b) {
  a->x = scalar * b->x;
  a->y = scalar * b->y;
  a->z = scalar * b->z;
  a->w = scalar * b->w;
}

void vec4_div(VEC4 *a, float diviser, VEC4 *b) {
  a->x = b->x / diviser;
  a->y = b->y / diviser;
  a->z = b->z / diviser;
  a->w = b->w / diviser;
}

long vec4_toColor(VEC4 *a) {
  return ((int)(a->a * 255) << 24) + ((int)(a->r * 255) << 16) + ((int)(a->g * 255) << 8) + (int)(a->b * 255);
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

void matrix3_apply_to_vector(VEC3 *vector, MATRIX3 *matrix) {
  VEC3 temp = { 0 };
  temp.x = matrix->m00 * vector->x + matrix->m01 * vector->y + matrix->m02;
  temp.y = matrix->m10 * vector->x + matrix->m11 * vector->y + matrix->m12;

  *vector = temp;
}


float angle_normalize(float angle) {
  angle = (float)fmod(angle, 2.0f * (float)M_PI);
  
  return angle >= 0 ? angle : angle + 2.0f * (float)M_PI;
}
