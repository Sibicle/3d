#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
  float x;
  float y;
} vec2_t;

typedef struct {
  float x;
  float y;
  float z;
} vec3_t;

const vec3_t VEC3_ZERO;
const vec3_t VEC3_ONE;

float vec2_length(vec2_t v);
vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_scale(vec2_t v, float s);
vec2_t vec2_div(vec2_t v, float s);

float vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_scale(vec3_t v, vec3_t s);
vec3_t vec3_scale_uniform(vec3_t v, float s);
vec3_t vec3_div(vec3_t v, float s);
vec3_t vec3_cross(vec3_t a, vec3_t b);

vec3_t tri_normal(vec3_t a, vec3_t b, vec3_t c);
vec3_t tri_centroid(vec3_t a, vec3_t b, vec3_t c);

vec3_t vec3_rotate_x(vec3_t v, float a);
vec3_t vec3_rotate_y(vec3_t v, float a);
vec3_t vec3_rotate_z(vec3_t v, float a);

void vec3_to_string(char * str, vec3_t v);

#endif
