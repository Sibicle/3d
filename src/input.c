#include <stdio.h>

#include "config.h"
#include "input.h"
#include "camera.h"
#include "mesh.h"
#include "mesh_files.h"
#include "origin.h"

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch(event.type) {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
        case SDLK_ESCAPE:
          is_running = false;
          break;
        case SDLK_x:
          fov_factor = fmin(fov_factor + 20, 800);
          break;
        case SDLK_z:
          fov_factor = fmax(fov_factor - 20, 128);
          break;
        case SDLK_a:
          camera_pos.x -= 0.1;
          print_camera_pos();
          break;
        case SDLK_d:
          camera_pos.x += 0.1;
          print_camera_pos();
          break;
        case SDLK_w:
          camera_pos.y += 0.1;
          print_camera_pos();
          break;
        case SDLK_s:
          camera_pos.y -= 0.1;
          print_camera_pos();
          break;
        case SDLK_e:
          camera_pos.z += 0.1;
          print_camera_pos();
          break;
        case SDLK_q:
          camera_pos.z -= 0.1;
          print_camera_pos();
          break;

        case SDLK_RIGHT:
          mesh.position.x += 0.1;
          mesh_print_pos();
          break;
        case SDLK_LEFT:
          mesh.position.x -= 0.1;
          mesh_print_pos();
          break;
        case SDLK_UP:
          mesh.position.y += 0.1;
          mesh_print_pos();
          break;
        case SDLK_DOWN:
          mesh.position.y -= 0.1;
          mesh_print_pos();
          break;
        case SDLK_PERIOD:
          mesh.position.z += 0.1;
          mesh_print_pos();
          break;
        case SDLK_COMMA:
          mesh.position.z -= 0.1;
          mesh_print_pos();
          break;

        case SDLK_SPACE:
          load_next_mesh_file();
          break;
        case SDLK_EQUALS:
          scale_mesh_uniform(1.1);
          break;
        case SDLK_MINUS:
          scale_mesh_uniform(0.9);
          break;

        case SDLK_f:
          render_faces = !render_faces;
          break;
        case SDLK_g:
          render_lines = !render_lines;
          break;
        case SDLK_v:
          render_vertices = !render_vertices;
          break;
        case SDLK_c:
          render_centroids = !render_centroids;
          break;
        case SDLK_n:
          render_normals = !render_normals;
          break;
        case SDLK_o:
          render_origin = !render_origin;
          break;
        case SDLK_r:
          render_camera_ray = !render_camera_ray;
          break;
        case SDLK_1:
          render_colors = !render_colors;
          break;

        case SDLK_b:
          cull_faces = (cull_faces + 1) % 3;
          break;

        case SDLK_SLASH:
          move_camera_w_mouse = !move_camera_w_mouse;
          break;
      }
      break;
  }

  SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
}
