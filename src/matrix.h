#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
  float m[4][4];
} mat4_t;

mat4_t mat4_make_identity(void);
mat4_t mat4_make_scale(float sx, float sy, float sz);
mat4_t mat4_make_scale_uniform(float s);

void mat4_mul_vec4_inplace(mat4_t * m, vec4_t * v);

void mat4_to_string(char * str, mat4_t * m);

#endif