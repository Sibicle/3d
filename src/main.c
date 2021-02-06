#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "array.h"
#include "vector.h"
#include "display.h"
#include "input.h"
#include "mesh_files.h"
#include "mesh.h"
#include "origin.h"
#include "camera.h"

void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );

  load_mesh_files();
  load_next_mesh_file();
}

void update(void) {
  int wait_time = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  if (wait_time > 0 && wait_time <= FRAME_TARGET_TIME) {
    SDL_Delay(wait_time);
  }

  previous_frame_time = SDL_GetTicks();

  projected_triangles = 0;
  projected_normals   = 0;
  projected_centroids = 0;

  if (true == move_camera_w_mouse) {
    camera_pos.y = ( mouse_y - (window_height / 2)) / -200.0;
    camera_pos.x = ( mouse_x - (window_width  / 2)) / 200.0;
  } else {
    mesh.rotation.x = ( mouse_y - (window_height / 2)) / -200.0;
    mesh.rotation.y = ( mouse_x - (window_width  / 2)) / 200.0;
  }

  for (int i = 0; i < array_length(mesh.faces); i++) {
    face_t mesh_face = mesh.faces[i];
    vec3_t normal    = mesh.normals[i];
    vec3_t centroid  = mesh.centroids[i];

    vec3_t transformed_centroid = centroid;
    vec3_t transformed_normal = normal;

    transformed_centroid = vec3_rotate(transformed_centroid, mesh.rotation);
    transformed_centroid = vec3_add(transformed_centroid, mesh.position);

    transformed_normal = vec3_div(transformed_normal, vec3_length(normal) * 2);
    transformed_normal = vec3_add(centroid, transformed_normal);
    transformed_normal = vec3_rotate(transformed_normal, mesh.rotation);
    transformed_normal = vec3_add(transformed_normal, mesh.position);

    vec3_t face_vertices [3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    vec3_t transformed_vertices [3];

    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate(transformed_vertex, mesh.rotation);
      transformed_vertex = vec3_add(transformed_vertex, mesh.position);

      transformed_vertices[j] = transformed_vertex;
    }

    vec3_t a = transformed_vertices[0];
    vec3_t b = transformed_vertices[1];
    vec3_t c = transformed_vertices[2];

    vec3_t ab = vec3_sub(b, a);
    vec3_t ac = vec3_sub(c, a);

    vec3_t calc_normal = vec3_cross(ab, ac);

    vec3_t camera_ray = vec3_sub(camera_pos, a);
    float back_dot = vec3_dot(calc_normal, camera_ray);

    if (render_back_faces == false && back_dot < 0) {
      continue;
    }

    vec2_t projected_centroid;
    projected_centroid = project(transformed_centroid);
    array_push(projected_centroids, projected_centroid);

    vec2_t projected_normal;
    projected_normal = project(transformed_normal);
    array_push(projected_normals, projected_normal);

    triangle_t projected_triangle;
    for (int j = 0; j < 3; j++) {
      vec2_t projected_point;
      projected_point = project(transformed_vertices[j]);
      projected_triangle.points[j] = projected_point;
    }
    array_push(projected_triangles, projected_triangle);
  }
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  if (render_origin) {
    origin_render();
    mesh_origin_render();
  }

  for (int i = 0; i < array_length(projected_triangles); i++) {
    vec2_t normal;
    vec2_t centroid;

    triangle_t triangle = projected_triangles[i];

    if (render_faces) {
      draw_triangle(
        triangle.points[0].x, triangle.points[0].y,
        triangle.points[1].x, triangle.points[1].y,
        triangle.points[2].x, triangle.points[2].y,
        GREEN
      );
    }

    if (render_vertices) {
      for(int j = 0; j < 3; j++) {
        draw_rect(
          triangle.points[j].x - 1, triangle.points[j].y - 1,
          3, 3,
          YELLOW, YELLOW
        );
      }
    }

    if (render_centroids) {
      centroid = projected_centroids[i];

      draw_rect(
        centroid.x - 1, centroid.y - 1,
        3, 3,
        RED, RED
      );
    }

    if (render_camera_ray) {
      centroid = projected_centroids[i];

      camera_ray_render();

      draw_line(
        projected_camera_pos.x, projected_camera_pos.y,
        centroid.x, centroid.y,
        PURPLE
      );
    }

    if (render_normals) {
      normal = projected_normals[i];
      centroid = projected_centroids[i];

      draw_line(
        centroid.x, centroid.y,
        normal.x, normal.y,
        RED
      );
    }
  }

  array_free(projected_triangles);
  array_free(projected_normals);
  array_free(projected_centroids);

  render_color_buffer();
  clear_color_buffer(BG);

  SDL_RenderPresent(renderer);
}

void free_resources() {
  free(color_buffer);
  free_mesh();
  free_mesh_files();
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
  free_resources();

  return 0;
}
