#include "input.h"
#include "camera.h"
#include "mesh.h"
#include "mesh_files.h"

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
        case SDLK_w:
          camera_pos.z += 0.1;
          break;
        case SDLK_s:
          camera_pos.z -= 0.1;
          break;
        case SDLK_a:
          camera_pos.x += 0.1;
          break;
        case SDLK_d:
          camera_pos.x -= 0.1;
          break;
        case SDLK_SPACE:
          load_next_mesh_file();
          break;
      }
      break;
  }

  SDL_GetGlobalMouseState(&mouse_x, &mouse_y);
}
