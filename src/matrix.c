#include <stdio.h>
#include <math.h>

#include "matrix.h"

mat4_t mat4_make_identity(void) {
  mat4_t m = {{ 0 }};

  m.m[0][0] = 1.0;
  m.m[1][1] = 1.0;
  m.m[2][2] = 1.0;
  m.m[3][3] = 1.0;

  return m;
}

mat4_t mat4_make_scale(float sx, float sy, float sz) {
  mat4_t m = mat4_make_identity();

  m.m[0][0] = sx;
  m.m[1][1] = sy;
  m.m[2][2] = sz;

  return m;
}

mat4_t mat4_make_scale_uniform(float s) {
  return mat4_make_scale(s, s, s);
}

mat4_t mat4_make_trans(float tx, float ty, float tz) {
  mat4_t m = mat4_make_identity();

  m.m[0][3] = tx;
  m.m[1][3] = ty;
  m.m[2][3] = tz;

  return m;
}

mat4_t mat4_make_rotate_x(float rx) {
  mat4_t m = mat4_make_identity();
  float  s = sin(rx);
  float  c = cos(rx);

  m.m[1][1] = c;
  m.m[1][2] = -s;

  m.m[2][1] = s;
  m.m[2][2] = c;

  return m;
}

mat4_t mat4_make_rotate_y(float ry) {
  mat4_t m = mat4_make_identity();
  float  s = sin(ry);
  float  c = cos(ry);

  m.m[0][0] = c;
  m.m[0][2] = s;

  m.m[2][0] = -s;
  m.m[2][2] = c;

  return m;
}

mat4_t mat4_make_rotate_z(float rz) {
  mat4_t m = mat4_make_identity();
  float  s = sin(rz);
  float  c = cos(rz);

  m.m[0][0] = c;
  m.m[0][1] = -s;

  m.m[1][0] = s;
  m.m[1][1] = c;

  return m;
}

void mat4_mul_vec4(mat4_t * m, vec4_t * v) {
  vec4_t prod = VEC4_ZERO;

  prod.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
  prod.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
  prod.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
  prod.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;

  v->x = prod.x;
  v->y = prod.y;
  v->z = prod.z;
  v->w = prod.w;
}

void mat4_mul_mat4(mat4_t * m, mat4_t * n) {
  mat4_t r = {{ 0 }};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      r.m[i][j] = m->m[i][0] * n->m[0][j]
                + m->m[i][1] * n->m[1][j]
                + m->m[i][2] * n->m[2][j]
                + m->m[i][3] * n->m[3][j];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m->m[i][j] = r.m[i][j];
    }
  }
}

void mat4_to_string(char * str, mat4_t * m) {
  int len = 0;

  len += sprintf(str + len, "┌ %0.1f  %0.1f  %0.1f  %0.1f  ┐\n", m->m[0][0], m->m[0][1], m->m[0][2], m->m[0][3]);
  len += sprintf(str + len, "│ %0.1f  %0.1f  %0.1f  %0.1f  │\n", m->m[1][0], m->m[1][1], m->m[1][2], m->m[1][3]);
  len += sprintf(str + len, "│ %0.1f  %0.1f  %0.1f  %0.1f  │\n", m->m[2][0], m->m[2][1], m->m[2][2], m->m[2][3]);
  len += sprintf(str + len, "└ %0.1f  %0.1f  %0.1f  %0.1f  ┘\n", m->m[3][0], m->m[3][1], m->m[3][2], m->m[3][3]);
}
