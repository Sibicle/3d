#include <math.h>
#include "vector.h"

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
