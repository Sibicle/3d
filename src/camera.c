#include <stdio.h>

#include "camera.h"
#include "origin.h"
#include "display.h"
#include "vector.h"

float fov_factor = 640;
vec3_t camera_pos = { .x = 0, .y = 0, .z = 5 };
vec2_t projected_camera_pos = { .x = 0, .y = 0 };
bool render_camera_ray = RENDER_CAMERA_RAY;

vec2_t project(vec3_t point) {
  vec3_t point_from_camera = vec3_add(point, camera_pos);

  vec2_t projected_point = {
    .x = (fov_factor * point_from_camera.x) / point_from_camera.z,
    .y = (fov_factor * point_from_camera.y) / point_from_camera.z
  };

  projected_point = vec2_add(projected_point, window_center);

  return projected_point;
}

void camera_ray_render(void) {
  projected_camera_pos = project(camera_pos);

  vec2_t projected_origin = project(origin);

  draw_rect(
    projected_origin.x - 1, projected_origin.y - 1,
    3, 3,
    ORANGE,
    ORANGE
  );

  draw_line(
    projected_origin.x, projected_origin.y,
    projected_camera_pos.x, projected_camera_pos.y,
    PURPLE
  );
}

void print_camera_pos(void) {
  char str[1024];
  vec3_to_string(str, camera_pos);
  printf("camera: %s\n", str);
}
