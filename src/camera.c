#include "camera.h"
#include "origin.h"
#include "display.h"

float fov_factor = 640;
vec3_t camera_pos = { .x = 0, .y = 0, .z = 0 };
vec2_t projected_camera_pos = { .x = 0, .y = 0 };
bool render_camera_ray = RENDER_CAMERA_RAY;

vec2_t project(vec3_t point) {
  vec2_t projected_point = {
    .x = (fov_factor * point.x) / point.z,
    .y = (fov_factor * point.y) / point.z
  };
  return projected_point;
}

void camera_ray_render(void) {
  projected_camera_pos = project(camera_pos);
  projected_camera_pos = vec2_add(projected_camera_pos, window_center);

  vec2_t projected_origin = project(origin);
  projected_origin = vec2_add(projected_origin, window_center);

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
