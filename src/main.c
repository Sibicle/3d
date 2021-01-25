#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "vars.h"

#include "display.h"
#include "vector.h"
#include "input.h"

vec3_t camera_pos = { .x = 0, .y = 0, .z = -5 };

void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );

  int point_arr_i = 0;

  for(float x = -1; x <= 1; x += 0.25) {
    for(float y = -1; y <= 1; y += 0.25) {
      for(float z = -1; z <= 1; z += 0.25) {
        vec3_t new_point = { .x = x, .y = y, .z = z };
        cube_points[point_arr_i++] = new_point;
      }
    }
  }
}

vec2_t project(vec3_t point) {
  vec2_t projected_point = {
    .x = (fov_factor * point.x) / point.z,
    .y = (fov_factor * point.y) / point.z
  };
  return projected_point;
}

vec2_t translate(vec2_t point, vec2_t trans) {
  vec2_t translated_point = {
    .x = point.x + trans.x,
    .y = point.y + trans.y
  };
  return translated_point;
}

void update(void) {
  cube_rotation.x += cube_velocity.x;
  cube_rotation.y += cube_velocity.y;
  cube_rotation.z += cube_velocity.z;

  for(int i = 0; i < N_POINTS; i++) {
    vec3_t point = cube_points[i];
    vec3_t point_r = vec3_rotate_x(vec3_rotate_y(point, cube_rotation.x), cube_rotation.y);

    point_r.z -= camera_pos.z;

    vec2_t projected_point = project(point_r);

    projected_points[i] = projected_point;
  }
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  vec2_t trans = {
    .x = (window_width / 2),
    .y = (window_height / 2)
  };

  for(int i = 0; i < N_POINTS; i++) {
    vec2_t projected_point = translate(projected_points[i], trans);
    draw_rect(projected_point.x, projected_point.y, 1, 1, YELLOW, YELLOW);
  }

  render_color_buffer();
  clear_color_buffer(BG);

  SDL_RenderPresent(renderer);
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }

  destroy_window();

  return 0;
}
