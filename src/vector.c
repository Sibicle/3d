#include <math.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"

const vec3_t VEC3_ZERO = {
  .x = 0.0,
  .y = 0.0,
  .z = 0.0
};

const vec3_t VEC3_ONE = {
  .x = 1.0,
  .y = 1.0,
  .z = 1.0
};

const vec4_t VEC4_ZERO = {
  .x = 0.0,
  .y = 0.0,
  .z = 0.0,
  .w = 0.0
};

const vec4_t VEC4_ONE = {
  .x = 1.0,
  .y = 1.0,
  .z = 1.0,
  .w = 1.0
};

float vec2_length(vec2_t v) {
  return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t vec2_add(vec2_t a, vec2_t b) {
  vec2_t sum = {
    .x = a.x + b.x,
    .y = a.y + b.y,
  };

  return sum;
}

void vec2_add_inplace(vec2_t * a, vec2_t * b) {
  a->x = a->x + b->x;
  a->y = a->y + b->y;
}

void vec2_scale_inplace(vec2_t * a, float s) {
  a->x = a->x * s;
  a->y = a->y * s;
}

vec2_t vec2_sub(vec2_t a, vec2_t b) {
  vec2_t dif = {
    .x = a.x - b.x,
    .y = a.y - b.y,
  };

  return dif;
}

vec2_t vec2_scale(vec2_t v, float s) {
  vec2_t scale = {
    .x = v.x * s,
    .y = v.y * s,
  };

  return scale;
}

float vec2_dot(vec2_t a, vec2_t b) {
  return (a.x * b.x) + (a.y * b.y);
}

void vec2_normalize(vec2_t * a) {
  float length = vec2_length(* a);
  a->x = a->x / length;
  a->y = a->y / length;
}

//
// vec3 in place functions
//
void vec3_add_inplace(vec3_t * a, vec3_t b) {
  a->x = a->x + b.x;
  a->y = a->y + b.y;
  a->z = a->z + b.z;
}

void vec3_sub_inplace(vec3_t * a, vec3_t b) {
  a->x = a->x - b.x;
  a->y = a->y - b.y;
  a->z = a->z - b.z;
}

void vec3_scale_inplace(vec3_t * a, vec3_t s) {
  a->x = a->x * s.x;
  a->y = a->y * s.y;
  a->z = a->z * s.z;
}

void vec3_scale_uniform_inplace(vec3_t * a, float s) {
  a->x = a->x * s;
  a->y = a->y * s;
  a->z = a->z * s;
}

void vec3_normalize_inplace(vec3_t * a) {
  float length = vec3_length(* a);
  a->x = a->x / length;
  a->y = a->y / length;
  a->z = a->z / length;
}

void vec3_rotate_x_inplace(vec3_t * a, float t) {
  vec3_t a_1 = {
    .x = a->x,
    .y = a->y * cos(t) - a->z * sin(t),
    .z = a->y * sin(t) + a->z * cos(t)
  };

  memcpy(a, &a_1, sizeof a_1);
}

void vec3_rotate_y_inplace(vec3_t * a, float t) {
  vec3_t a_1 = {
    .x =  a->x * cos(t) + a->z * sin(t),
    .y =  a->y,
    .z = -a->x * sin(t) + a->z * cos(t)
  };

  memcpy(a, &a_1, sizeof a_1);
}

void vec3_rotate_z_inplace(vec3_t * a, float t) {
  vec3_t a_1 = {
    .x = a->x * cos(t) - a->y * sin(t),
    .y = a->x * sin(t) + a->y * cos(t),
    .z = a->z
  };

  memcpy(a, &a_1, sizeof a_1);
}

void vec3_rotate_inplace(vec3_t * a, vec3_t t) {
  vec3_rotate_x_inplace(a, t.x);
  vec3_rotate_y_inplace(a, t.y);
  vec3_rotate_z_inplace(a, t.z);
}

//
// vector operations returning a scalar
//
float vec3_length(vec3_t v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float vec3_dot(vec3_t a, vec3_t b) {
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3_t vec3_add(vec3_t a, vec3_t b) {
  vec3_t sum = {
    .x = a.x + b.x,
    .y = a.y + b.y,
    .z = a.z + b.z
  };

  return sum;
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
  vec3_t dif = {
    .x = a.x - b.x,
    .y = a.y - b.y,
    .z = a.z - b.z
  };

  return dif;
}

vec3_t vec3_scale(vec3_t v, vec3_t s) {
  vec3_t scale = {
    .x = v.x * s.x,
    .y = v.y * s.y,
    .z = v.z * s.z
  };

  return scale;
}

vec3_t vec3_scale_uniform(vec3_t v, float s) {
  vec3_t scale = {
    .x = v.x * s,
    .y = v.y * s,
    .z = v.z * s
  };

  return scale;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  vec3_t cross = {
    .x = a.y * b.z - a.z * b.y,
    .y = a.z * b.x - a.x * b.z,
    .z = a.x * b.y - a.y * b.x
  };
  return cross;
}

vec4_t vec4_cross(vec4_t * a, vec4_t * b) {
  vec4_t cross = {
    .x = a->y * b->z - a->z * b->y,
    .y = a->z * b->x - a->x * b->z,
    .z = a->x * b->y - a->y * b->x,
    .w = 1.0
  };

  return cross;
}

float vec4_dot(vec4_t * a, vec4_t * b) {
  return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}

vec4_t vec4_sub(vec4_t * a, vec4_t * b) {
  vec4_t dif = {
    .x = a->x - b->x,
    .y = a->y - b->y,
    .z = a->z - b->z,
    .w = 1
  };

  return dif;
}

vec4_t vec4_centroid(vec4_t * a, vec4_t * b, vec4_t * c) {
  vec4_t centroid = {
    .x = (a->x + b->x + c->x) / 3.0,
    .y = (a->y + b->y + c->y) / 3.0,
    .z = (a->z + b->z + c->z) / 3.0,
    .w = 1.0
  };

  return centroid;
}

vec4_t vec4_normal(vec4_t * a, vec4_t * b, vec4_t * c) {
  vec4_t ab     = vec4_sub(b, a);
  vec4_t ac     = vec4_sub(c, a);
  vec4_t normal = vec4_cross(&ab, &ac);

  return normal;
}

vec3_t vec3_rotate_x(vec3_t v, float a) {
  vec3_t v_1 = {
    .x = v.x,
    .y = v.y * cos(a) - v.z * sin(a),
    .z = v.y * sin(a) + v.z * cos(a)
  };

  return v_1;
}

vec3_t vec3_rotate_y(vec3_t v, float a) {
  vec3_t v_1 = {
    .x = v.x * cos(a) - v.z * sin(a),
    .y = v.y,
    .z = v.x * sin(a) + v.z * cos(a)
  };

  return v_1;
}

vec3_t vec3_rotate_z(vec3_t v, float a) {
  vec3_t v_1 = {
    .x = v.x * cos(a) - v.y * sin(a),
    .y = v.x * sin(a) + v.y * cos(a),
    .z = v.z
  };

  return v_1;
}

vec3_t vec3_from_vec4(vec4_t * v) {
  vec3_t w = {
    .x = v->x,
    .y = v->y,
    .z = v->z
  };

  return w;
}

//
// vec4 operations
//
vec4_t vec4_from_vec3(vec3_t * v) {
  vec4_t w = {
    .x = v->x,
    .y = v->y,
    .z = v->z,
    .w = 1.0
  };

  return w;
}

//
// vector utility functions
//
vec3_t vec3_rotate(vec3_t v, vec3_t r) {
  vec3_t rotated = v;

  rotated = vec3_rotate_x(rotated, r.x);
  rotated = vec3_rotate_y(rotated, r.y);
  rotated = vec3_rotate_z(rotated, r.z);

  return rotated;
}

void vec3_to_string(char * str, vec3_t * v) {
  sprintf(str, "[ %0.1f, %0.1f, %0.1f ]", v->x, v->y, v->z);
}

void vec4_to_string(char * str, vec4_t * v) {
  int len = 0;

  len += sprintf(str + len, "┌ %6.2f ┐\n", v->x);
  len += sprintf(str + len, "│ %6.2f │\n", v->y);
  len += sprintf(str + len, "│ %6.2f │\n", v->z);
  len += sprintf(str + len, "└ %6.2f ┘\n", v->w);
}
