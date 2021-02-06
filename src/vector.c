#include <math.h>
#include <stdio.h>

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

vec2_t vec2_div(vec2_t v, float s) {
  vec2_t quo = {
    .x = v.x / s,
    .y = v.y / s,
  };

  return quo;
}

float vec3_length(vec3_t v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
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

vec3_t vec3_div(vec3_t v, float s) {
  vec3_t quo = {
    .x = v.x / s,
    .y = v.y / s,
    .z = v.z / s
  };

  return quo;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
  vec3_t cross = {
    .x = a.y * b.z - a.z * b.y,
    .y = a.z * b.x - a.x * b.z,
    .z = a.x * b.y - a.y * b.x
  };
  return cross;
}

vec3_t tri_normal(vec3_t a, vec3_t b, vec3_t c) {
  vec3_t ab     = vec3_sub(b, a);
  vec3_t ac     = vec3_sub(c, a);
  vec3_t normal = vec3_cross(ab, ac);

  return normal;
}

vec3_t tri_centroid(vec3_t a, vec3_t b, vec3_t c) {
  vec3_t centroid = {
    .x = (a.x + b.x + c.x) / 3,
    .y = (a.y + b.y + c.y) / 3,
    .z = (a.z + b.z + c.z) / 3
  };

  return centroid;
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

vec3_t vec3_rotate(vec3_t v, vec3_t r) {
  vec3_t rotated = v;

  rotated = vec3_rotate_x(rotated, r.x);
  rotated = vec3_rotate_y(rotated, r.y);
  rotated = vec3_rotate_z(rotated, r.z);

  return rotated;
}

void vec3_to_string(char * str, vec3_t v) {
  sprintf(str, "(%f, %f, %f)", v.x + 0.0, v.y + 0.0, v.z + 0.0);
}
