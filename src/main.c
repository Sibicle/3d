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

#define RENDER_FACES     true
#define RENDER_CENTROIDS true
#define RENDER_NORMALS   true
#define RENDER_VERTICES  true

void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );

  vec3_t translate = VEC3_ZERO;
  translate.y = -1;

  vec3_t rotate = VEC3_ZERO;
  rotate.x = M_PI;

  vec3_t scale = VEC3_ONE;
  scale.x = 0.75;
  scale.y = 0.75;
  scale.z = 0.75;

  load_obj("assets/teapot.obj");
  transform_mesh(translate, rotate, scale);
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

  if (wait_time > 0 && wait_time <= FRAME_TARGET_TIME) {
    SDL_Delay(wait_time);
  }

  previous_frame_time = SDL_GetTicks();

  projected_triangles = 0;
  projected_normals   = 0;
  projected_centroids = 0;

  vec2_t trans = {
    .x = (window_width / 2),
    .y = (window_height / 2)
  };

  mesh.rotation.x = ( mouse_y - (window_height / 2)) / 200.0;
  mesh.rotation.y = ( mouse_x - (window_width  / 2)) / 200.0;

  for (int i = 0; i < array_length(mesh.faces); i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices [3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    triangle_t projected_triangle;

    for (int j = 0; j < 3; j++) {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_rotate(transformed_vertex, mesh.rotation);
      transformed_vertex = vec3_sub(transformed_vertex, camera_pos);

      vec2_t projected_point;
      projected_point = project(transformed_vertex);
      projected_point = translate(projected_point, trans);

      projected_triangle.points[j] = projected_point;
    }

    array_push(projected_triangles, projected_triangle);

    vec3_t centroid;
    vec3_t normal;

    if (RENDER_CENTROIDS || RENDER_NORMALS) {
      centroid = mesh.centroids[i];

      vec3_t transformed_centroid = centroid;

      transformed_centroid = vec3_rotate(transformed_centroid, mesh.rotation);
      transformed_centroid = vec3_sub(transformed_centroid, camera_pos);

      vec2_t projected_centroid;

      projected_centroid = project(transformed_centroid);
      projected_centroid = translate(projected_centroid, trans);

      array_push(projected_centroids, projected_centroid);
    }

    if (RENDER_NORMALS) {
      normal = mesh.normals[i];

      vec3_t transformed_normal_vertex = normal;

      transformed_normal_vertex = vec3_div(normal, vec3_length(normal) * 2);
      transformed_normal_vertex = vec3_add(centroid, transformed_normal_vertex);
      transformed_normal_vertex = vec3_rotate(transformed_normal_vertex, mesh.rotation);
      transformed_normal_vertex = vec3_sub(transformed_normal_vertex, camera_pos);

      vec2_t projected_normal_vertex;

      projected_normal_vertex = project(transformed_normal_vertex);
      projected_normal_vertex = translate(projected_normal_vertex, trans);

      array_push(projected_normals, projected_normal_vertex);
    }
  }
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  for (int i = 0; i < array_length(projected_triangles); i++) {
    triangle_t triangle = projected_triangles[i];
    vec2_t normal;
    vec2_t centroid;

    if (RENDER_FACES) {
      draw_triangle(
        triangle.points[0].x, triangle.points[0].y,
        triangle.points[1].x, triangle.points[1].y,
        triangle.points[2].x, triangle.points[2].y,
        GREEN
      );
    }

    if (RENDER_VERTICES) {
      for(int j = 0; j < 3; j++) {
        draw_rect(
          triangle.points[j].x - 1, triangle.points[j].y - 1,
          3, 3,
          YELLOW, YELLOW
        );
      }
    }

    if (RENDER_CENTROIDS) {
      centroid = projected_centroids[i];

      draw_rect(
        centroid.x - 1, centroid.y - 1,
        3, 3,
        RED, RED
      );
    }

    if (RENDER_NORMALS) {
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
