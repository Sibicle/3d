#include "input.h"
#include "vars.h"

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
        case SDLK_UP:
          grid_size = fmin(grid_size + 1, fmin(20, grid_spacing));
          break;
        case SDLK_DOWN:
          grid_size = fmax(grid_size - 1, 1);
          break;
        case SDLK_RIGHT:
          grid_spacing = fmin(grid_spacing + 1, 40);
          break;
        case SDLK_LEFT:
          grid_spacing = fmax(grid_spacing - 1, 1);
          grid_size = fmin(grid_size, grid_spacing);
          break;
        case SDLK_w:
          box_y = fmax(box_y - box_speed, 0);
          break;
        case SDLK_s:
          box_y = fmin(box_y + box_speed, window_height - box_h);
          break;
        case SDLK_a:
          box_x = fmax(box_x - box_speed, 0);
          break;
        case SDLK_d:
          box_x = fmin(box_x + box_speed, window_width - box_w);
          break;
        case SDLK_SPACE:
          box_stroke = colors[rand_int(0, 7)];
          break;
        case SDLK_x:
          fov_factor = fmin(fov_factor + 20, 800);
          break;
        case SDLK_z:
          fov_factor = fmax(fov_factor - 20, 128);
          break;
      }
      break;
  }

  int mouse_x, mouse_y;
  SDL_GetGlobalMouseState( &mouse_x, &mouse_y );

  cube_velocity.x = ( mouse_x - (window_width / 2)) / 2000.0;
  cube_velocity.y = ( mouse_y - (window_height / 2)) / 2000.0;
}
