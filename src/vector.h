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

void vec2_normalize(vec2_t * a);

float vec2_dot(vec2_t a, vec2_t b);
float vec2_length(vec2_t a);

void vec2_add_inplace(vec2_t * a, vec2_t * b);
void vec2_scale_inplace(vec2_t * a, float s);

vec2_t vec2_add(vec2_t a, vec2_t b);
vec2_t vec2_sub(vec2_t a, vec2_t b);
vec2_t vec2_scale(vec2_t a, float s);

void vec3_add_inplace(vec3_t * a, vec3_t b);
void vec3_sub_inplace(vec3_t * a, vec3_t b);
void vec3_scale_inplace(vec3_t * a, vec3_t s);
void vec3_scale_uniform_inplace(vec3_t * a, float s);
void vec3_normalize_inplace(vec3_t * a);
void vec3_rotate_x_inplace(vec3_t * a, float t);
void vec3_rotate_y_inplace(vec3_t * a, float t);
void vec3_rotate_z_inplace(vec3_t * a, float t);
void vec3_rotate_inplace(vec3_t * a, vec3_t t);

float vec3_length(vec3_t v);
float vec3_dot(vec3_t a, vec3_t b);

vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_sub(vec3_t a, vec3_t b);
vec3_t vec3_scale(vec3_t v, vec3_t s);
vec3_t vec3_scale_uniform(vec3_t v, float s);
vec3_t vec3_cross(vec3_t a, vec3_t b);

vec3_t vec3_rotate_x(vec3_t v, float a);
vec3_t vec3_rotate_y(vec3_t v, float a);
vec3_t vec3_rotate_z(vec3_t v, float a);
vec3_t vec3_rotate(vec3_t v, vec3_t t);

vec3_t tri_normal(vec3_t a, vec3_t b, vec3_t c);
vec3_t tri_centroid(vec3_t a, vec3_t b, vec3_t c);

void vec3_to_string(char * str, vec3_t v);

#endif
