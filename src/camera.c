#include <stdio.h>

#include "config.h"
#include "camera.h"
#include "origin.h"
#include "display.h"
#include "vector.h"

float fov_factor = 640;
vec3_t camera_pos = { .x = 0, .y = 0, .z = -5 };
vec2_t projected_camera_pos = { .x = 0, .y = 0 };

vec2_t project(vec3_t point) {
  vec3_t point_from_camera = vec3_sub(point, camera_pos);

  vec2_t projected_point = {
    .x = (fov_factor * point_from_camera.x) / point_from_camera.z,
    .y = (fov_factor * point_from_camera.y) / point_from_camera.z
  };

  projected_point = vec2_add(projected_point, window_center);

  return projected_point;
}

void camera_ray_render(void) {
  vec3_t prime_camera_pos  = camera_pos;
  prime_camera_pos.z       = prime_camera_pos.z + 1;
  projected_camera_pos     = project(prime_camera_pos);
}

void print_camera_pos(void) {
  if (DEBUG_MODE) {
    char str[1024];
    vec3_to_string(str, camera_pos);
    printf("camera: %s\n", str);
  }
}
