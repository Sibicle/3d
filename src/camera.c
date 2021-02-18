#include <stdio.h>

#include "camera.h"
#include "config.h"
#include "origin.h"
#include "display.h"

float fov_factor = 640;
vec4_t camera_pos = { .x = 0.0, .y = 0.0, .z = -5.0, .w = 1.0 };
vec2_t projected_camera_pos = { .x = 0, .y = 0 };

vec2_t project(vec3_t point) {
  vec3_t point_from_camera = vec3_sub(point, vec3_from_vec4(&camera_pos));

  vec2_t projected_point = {
    .x = (fov_factor * point_from_camera.x) / point_from_camera.z,
    .y = (fov_factor * point_from_camera.y) / point_from_camera.z
  };

  projected_point = vec2_add(projected_point, window_center);

  return projected_point;
}

void print_camera_pos(void) {
  char str[1024];
  vec4_to_string(str, &camera_pos);
  printf("camera: %s\n", str);
}
