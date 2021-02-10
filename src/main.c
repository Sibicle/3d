#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "array.h"
#include "vector.h"
#include "matrix.h"
#include "display.h"
#include "input.h"
#include "mesh_files.h"
#include "mesh.h"
#include "origin.h"
#include "camera.h"

void setup(void) {
  color_buffer = (color_t*) malloc(sizeof(color_t) * window_width * window_height);

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

  if (true == move_camera_w_mouse) {
    camera_pos.y = ( mouse_y - (window_height / 2)) / -200.0;
    camera_pos.x = ( mouse_x - (window_width  / 2)) / 200.0;
  } else {
    mesh.rotation.x = ( mouse_y - (window_height / 2)) / -200.0;
    mesh.rotation.y = ( mouse_x - (window_width  / 2)) / -200.0;
  }

  mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
  mat4_t trans_matrix = mat4_make_trans(mesh.position.x, mesh.position.y, mesh.position.z);
  mat4_t rotate_x_matrix = mat4_make_rotate_x(mesh.rotation.x);
  mat4_t rotate_y_matrix = mat4_make_rotate_y(mesh.rotation.y);
  mat4_t rotate_z_matrix = mat4_make_rotate_z(mesh.rotation.z);

  for (int i = 0; i < array_length(mesh.faces); i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices [3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    vec4_t transformed_vertices [3];

    for (int j = 0; j < 3; j++) {
      vec4_t transformed_vertex = vec4_from_vec3(&face_vertices[j]);

      mat4_mul_vec4_inplace(&scale_matrix, &transformed_vertex);
      mat4_mul_vec4_inplace(&trans_matrix, &transformed_vertex);
      mat4_mul_vec4_inplace(&rotate_x_matrix, &transformed_vertex);
      mat4_mul_vec4_inplace(&rotate_y_matrix, &transformed_vertex);
      mat4_mul_vec4_inplace(&rotate_z_matrix, &transformed_vertex);

      transformed_vertices[j] = transformed_vertex;
    }

    vec3_t a = vec3_from_vec4(&transformed_vertices[0]);
    vec3_t b = vec3_from_vec4(&transformed_vertices[1]);
    vec3_t c = vec3_from_vec4(&transformed_vertices[2]);

    vec3_t centroid = tri_centroid(a, b, c);
    vec3_t normal = tri_normal(a, b, c);

    vec3_t camera_ray = vec3_sub(camera_pos, a);
    float back_dot = vec3_dot(normal, camera_ray);

    if (cull_faces == CULL_BACK_FACES && back_dot < 0) {
      continue;
    }

    if (cull_faces == CULL_FRONT_FACES && back_dot > 0) {
      continue;
    }

    normal = vec3_scale_uniform(normal, vec3_length(normal) * 2);
    normal = vec3_add(centroid, normal);

    triangle_t projected_triangle;

    for (int j = 0; j < 3; j++) {
      vec2_t projected_point;
      projected_point = project(vec3_from_vec4(&transformed_vertices[j]));
      projected_triangle.points[j] = projected_point;
    }

    projected_triangle.centroid      = project(centroid);
    projected_triangle.normal        = project(normal);
    projected_triangle.average_depth = centroid.z;

    projected_triangle.color         = mesh_face.color;

    array_push(projected_triangles, projected_triangle);
  }

  sort_triangles_by_depth(projected_triangles);
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  if (render_origin) {
    origin_render();
    mesh_origin_render();
  }

  for (int i = 0; i < array_length(projected_triangles); i++) {
    triangle_t triangle = projected_triangles[i];

    if (render_faces) {
      color_t color = render_colors ? triangle.color : PURPLE;
      draw_filled_triangle(
        triangle.points[0].x, triangle.points[0].y,
        triangle.points[1].x, triangle.points[1].y,
        triangle.points[2].x, triangle.points[2].y,
        color
      );
    }

    if (render_lines) {
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
      draw_rect(
        triangle.centroid.x - 1, triangle.centroid.y - 1,
        3, 3,
        RED, RED
      );
    }

    if (render_camera_ray) {
      camera_ray_render();

      draw_line(
        projected_camera_pos.x, projected_camera_pos.y,
        triangle.centroid.x, triangle.centroid.y,
        PURPLE
      );
    }

    if (render_normals) {
      draw_line(
        triangle.centroid.x, triangle.centroid.y,
        triangle.normal.x, triangle.normal.y,
        RED
      );
    }
  }

  array_free(projected_triangles);

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
