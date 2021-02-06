#include "origin.h"
#include "mesh.h"
#include "camera.h"
#include "display.h"

bool render_origin = RENDER_ORIGIN;

vec3_t origin = {
  .x = 0.0,
  .y = 0.0,
  .z = 0.0
};

vec3_t x_axis = {
  .x = 1.0,
  .y = 0.0,
  .z = 0.0
};

vec3_t y_axis = {
  .x = 0.0,
  .y = 1.0,
  .z = 0.0
};

vec3_t z_axis = {
  .x = 0.0,
  .y = 0.0,
  .z = 1.0
};

void origin_render() {
  vec3_t transformed_origin = origin;
  transformed_origin = vec3_rotate(transformed_origin, mesh.rotation);
  transformed_origin = vec3_sub(transformed_origin, camera_pos);
  vec2_t projected_origin;
  projected_origin = project(transformed_origin);
  projected_origin = vec2_add(projected_origin, window_center);

  draw_rect(
    projected_origin.x - 1, projected_origin.y - 1,
    3, 3,
    ORANGE,
    ORANGE
  );

  vec3_t transformed_x_axis = x_axis;
  transformed_x_axis = vec3_rotate(transformed_x_axis, mesh.rotation);
  transformed_x_axis = vec3_sub(transformed_x_axis, camera_pos);
  vec2_t projected_x_axis;
  projected_x_axis = project(transformed_x_axis);
  projected_x_axis = vec2_add(projected_x_axis, window_center);

  draw_line(
    projected_origin.x, projected_origin.y,
    projected_x_axis.x, projected_x_axis.y,
    RED
  );

  vec3_t transformed_y_axis = y_axis;
  transformed_y_axis = vec3_rotate(transformed_y_axis, mesh.rotation);
  transformed_y_axis = vec3_sub(transformed_y_axis, camera_pos);
  vec2_t projected_y_axis;
  projected_y_axis = project(transformed_y_axis);
  projected_y_axis = vec2_add(projected_y_axis, window_center);

  draw_line(
    projected_origin.x, projected_origin.y,
    projected_y_axis.x, projected_y_axis.y,
    GREEN
  );

  vec3_t transformed_z_axis = z_axis;
  transformed_z_axis = vec3_rotate(transformed_z_axis, mesh.rotation);
  transformed_z_axis = vec3_sub(transformed_z_axis, camera_pos);
  vec2_t projected_z_axis;
  projected_z_axis = project(transformed_z_axis);
  projected_z_axis = vec2_add(projected_z_axis, window_center);

  draw_line(
    projected_origin.x, projected_origin.y,
    projected_z_axis.x, projected_z_axis.y,
    CYAN
  );

}
