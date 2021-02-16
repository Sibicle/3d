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
// #include "origin.h"
#include "camera.h"
#include "light.h"

void setup(void) {
  color_buffer = (color_t*) malloc(sizeof(color_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );

  float fov    = M_PI  / 3.0;
  float aspect = (float)window_height / (float)window_width;
  float znear  = 0.1;
  float zfar   = 100;
  proj_matrix = mat4_make_persp(fov, aspect, znear, zfar);

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

  mat4_t world_matrix = mat4_make_world_matrix();

  mat4_t screen_matrix = mat4_make_screen_matrix();

  for (int i = 0; i < array_length(mesh.faces); i++) {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices [3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    vec4_t transformed_vertices [3];

    for (int j = 0; j < 3; j++) {
      vec4_t transformed_vertex = vec4_from_vec3(&face_vertices[j]);

      mat4_mul_vec4(&world_matrix, &transformed_vertex);

      transformed_vertices[j] = transformed_vertex;
    }

    vec4_t * a = &transformed_vertices[0];
    vec4_t * b = &transformed_vertices[1];
    vec4_t * c = &transformed_vertices[2];

    vec4_t centroid = vec4_centroid(a, b, c);
    vec4_t normal   = vec4_normal(a, b, c);

    vec4_t camera_ray = vec4_sub(&camera_pos, a);
    float back_dot = vec4_dot(&normal, &camera_ray);

    if (cull_faces == CULL_BACK_FACES && back_dot < 0) {
      continue;
    }

    if (cull_faces == CULL_FRONT_FACES && back_dot > 0) {
      continue;
    }

    vec3_t normal_normal = vec3_from_vec4(&normal);
    vec3_normalize_inplace(&normal_normal);

    vec3_t light_orientation = global_light.orientation;
    vec3_normalize_inplace(&light_orientation);

    float light_dot = vec3_dot(normal_normal, light_orientation);

    vec3_scale_uniform_inplace(&normal_normal, 0.5);
    vec4_t vec4_normal_normal = vec4_from_vec3(&normal_normal);
    vec4_add(&vec4_normal_normal, &centroid);

    triangle_t projected_triangle;

    projected_triangle.centroid      = mat4_mul_vec4_project(&proj_matrix, &centroid);
    projected_triangle.normal        = mat4_mul_vec4_project(&proj_matrix, &vec4_normal_normal);
    projected_triangle.average_depth = centroid.z;

    mat4_mul_vec4(&screen_matrix, &projected_triangle.centroid);

    projected_triangle.centroid.x += (window_width / 2.0);
    projected_triangle.centroid.y += (window_height / 2.0);

    mat4_mul_vec4(&screen_matrix, &projected_triangle.normal);

    projected_triangle.normal.x += (window_width / 2.0);
    projected_triangle.normal.y += (window_height / 2.0);

    light_dot = (light_dot + 1) / 2;
    color_t lit_color = light_apply_intensity(PURPLE, light_dot);
    projected_triangle.color = lit_color;

    for (int j = 0; j < 3; j++) {
      vec4_t projected_point = mat4_mul_vec4_project(&proj_matrix, &transformed_vertices[j]);

      mat4_mul_vec4(&screen_matrix, &projected_point);

      projected_triangle.points[j] = projected_point;

      projected_triangle.points[j].x += (window_width / 2.0);
      projected_triangle.points[j].y += (window_height / 2.0);
    }

    array_push(projected_triangles, projected_triangle);
  }

  sort_triangles_by_depth(projected_triangles);
}

void render(void) {
  draw_dots(grid_spacing, LINE);

  // if (render_origin) {
  //   origin_render();
  //   mesh_origin_render();
  // }

  for (int i = 0; i < array_length(projected_triangles); i++) {
    triangle_t triangle = projected_triangles[i];

    if (render_faces) {
      draw_filled_triangle(
        triangle.points[0].x, triangle.points[0].y,
        triangle.points[1].x, triangle.points[1].y,
        triangle.points[2].x, triangle.points[2].y,
        triangle.color
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
