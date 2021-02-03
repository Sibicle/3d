#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "array.h"
#include "util.h"
#include "vector.h"
#include "mesh.h"
#include "camera.h"
#include "display.h"
#include "input.h"


void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );
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
  int wait_time = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  if(wait_time > 0 && wait_time <= FRAME_TARGET_TIME) {
    SDL_Delay(wait_time);
  }

  previous_frame_time = SDL_GetTicks();

  projected_triangles = 0;

  vec2_t trans = {
    .x = (window_width / 2),
    .y = (window_height / 2)
  };

  mesh_velocity.x = ( mouse_y - (window_height / 2)) / 2000.0;
  mesh_velocity.y = ( mouse_x - (window_width / 2)) / 2000.0;

  mesh_rotation.x += mesh_velocity.x;
  mesh_rotation.y += mesh_velocity.y;
  mesh_rotation.z += mesh_velocity.z;

  for(int i = 0; i < N_CUBE_FACES; i++) {
    face_t cube_face = cube_faces[i];

    vec3_t face_verticies [3];
    face_verticies[0] = cube_vertices[cube_face.a - 1];
    face_verticies[1] = cube_vertices[cube_face.b - 1];
    face_verticies[2] = cube_vertices[cube_face.c - 1];

    triangle_t projected_triangle;

    for(int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_verticies[j];

      transformed_vertex = vec3_rotate_x(transformed_vertex, mesh_rotation.x);
      transformed_vertex = vec3_rotate_y(transformed_vertex, mesh_rotation.y);
      transformed_vertex = vec3_rotate_z(transformed_vertex, mesh_rotation.z);

      transformed_vertex.z -= camera_pos.z;

      vec2_t projected_point = project(transformed_vertex);
      projected_point = translate(projected_point, trans);

      projected_triangle.points[j] = projected_point;
    }

    array_push(projected_triangles, projected_triangle);
  }
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  int num_tri = array_length(projected_triangles);
  for(int i = 0; i < num_tri; i++) {
    triangle_t triangle = projected_triangles[i];

    for(int j = 0; j < 3; j++)
    {
      draw_rect(triangle.points[j].x - 1, triangle.points[j].y - 1, 3, 3, YELLOW, YELLOW);
    }

    draw_triangle(
      triangle.points[0].x, triangle.points[0].y,
      triangle.points[1].x, triangle.points[1].y,
      triangle.points[2].x, triangle.points[2].y,
      GREEN
    );
  }

  array_free(projected_triangles);

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
