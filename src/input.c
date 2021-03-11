#include <stdio.h>

#include "config.h"
#include "input.h"
#include "camera.h"
#include "mesh.h"
#include "mesh_files.h"
#include "origin.h"

int mouse_x = 0;
int mouse_y = 0;

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
          if (flags & DEBUG_MODE) print_camera_pos();
          break;
        case SDLK_d:
          camera_pos.x += 0.1;
          if (flags & DEBUG_MODE) print_camera_pos();
          break;
        case SDLK_w:
          camera_pos.y += 0.1;
          if (flags & DEBUG_MODE) print_camera_pos();
          break;
        case SDLK_s:
          camera_pos.y -= 0.1;
          if (flags & DEBUG_MODE) print_camera_pos();
          break;
        case SDLK_e:
          camera_pos.z += 0.1;
          if (flags & DEBUG_MODE) print_camera_pos();
          break;
        case SDLK_q:
          camera_pos.z -= 0.1;
          if (flags & DEBUG_MODE) print_camera_pos();
          break;

        case SDLK_RIGHT:
          mesh.position.x += 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
          break;
        case SDLK_LEFT:
          mesh.position.x -= 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
          break;
        case SDLK_UP:
          mesh.position.y += 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
          break;
        case SDLK_DOWN:
          mesh.position.y -= 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
          break;
        case SDLK_PERIOD:
          mesh.position.z += 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
          break;
        case SDLK_COMMA:
          mesh.position.z -= 0.1;
          if (flags & DEBUG_MODE) mesh_print_pos();
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

        case SDLK_g:
          flags ^= RENDER_LINES;
          break;
        case SDLK_f:
          flags ^= RENDER_FACES;
          break;
        case SDLK_r:
          flags ^= RENDER_COLORS;
          break;
        case SDLK_l:
          flags ^= RENDER_LIGHTING;
          break;
        case SDLK_t:
          flags ^= RENDER_TEXTURES;
          break;

        case SDLK_v:
          flags ^= SHOW_VERTICES;
          break;
        case SDLK_c:
          flags ^= SHOW_CENTROIDS;
          break;
        case SDLK_n:
          flags ^= SHOW_NORMALS;
          break;

        case SDLK_o:
          flags ^= SHOW_ORIGIN;
          break;
        case SDLK_p:
          flags ^= SHOW_CAMERA_RAY;
          break;

        case SDLK_y:
          flags ^= CULL_BACK_FACES;
          break;
        case SDLK_h:
          flags ^= CULL_FRONT_FACES;
          break;

        case SDLK_1:
          flags = FLAGS_TEXTURED;
          break;
        case SDLK_2:
          flags = FLAGS_SHADED;
          break;
        case SDLK_3:
          flags = FLAGS_WIREFRAME;
          break;
        case SDLK_4:
          flags = FLAGS_DEBUG_MATH;
          break;
        case SDLK_5:
          flags = FLAGS_DEBUG_SHADING;
          break;
        case SDLK_6:
          flags = FLAGS_DEBUG_TEXTURES;
          break;
      }
      break;
  }

  SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
}
