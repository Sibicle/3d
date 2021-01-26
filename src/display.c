#include "display.h"

uint32_t colors[7] = { CYAN, GREEN, ORANGE, PINK, PURPLE, RED, YELLOW };

int window_width       = 800;
int window_height      = 600;

SDL_Window* window     = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer            = NULL;

int previous_frame_time = 0;

int grid_size          = 1;
int grid_spacing       = 10;
int grid_type          = GRID_DOT;

int      box_x      = 10;
int      box_y      = 10;
int      box_w      = 20;
int      box_h      = 10;
int      box_speed  = 5;
uint32_t box_stroke = GREEN;


void draw_pixel(int x, int y, uint32_t color) {
  if (x >= 0 && x < window_width && y>= 0 && y < window_height) {
    color_buffer[(window_width * y) + x] = color;
  }
}

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "error initializing SDl");
    return false;
  }

  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  window_width = display_mode.w;
  window_height = display_mode.h - 29;

  window = SDL_CreateWindow(
    NULL,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    window_width,
    window_height,
    SDL_WINDOW_BORDERLESS
  );
  if (!window) {
    fprintf(stderr, "error creating SDL window");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "error creating SDL renderer");
    return false;
  }

  // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  SDL_PumpEvents();

  return true;
}

void render_color_buffer(void) {
  SDL_UpdateTexture(
    color_buffer_texture,
    NULL,
    color_buffer,
    (int) (window_width * sizeof(uint32_t))
  );

  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
  for(int y = 0; y < window_height; y++) {
    for(int x = 0; x < window_width; x++) {
      draw_pixel(x, y, color);
    }
  }
}

void draw_grid(int spacing, int size, uint32_t color) {
  for(int y = 0; y < window_height; y++) {
    for(int x = 0; x < window_width; x++) {
      if(x % spacing < size || y % spacing < size) {
        draw_pixel(x, y, color);
      }
    }
  }
}

void draw_dots(int spacing, uint32_t color) {
  for(int y = 0; y < window_height; y += spacing) {
    for(int x = 0; x < window_width; x += spacing) {
      draw_pixel(x, y, color);
    }
  }
}

void draw_rect(int x_pos, int y_pos, int w, int h, uint32_t color, uint32_t stroke) {
  for(int y = y_pos; y <= y_pos + h; y++) {
    for(int x = x_pos; x <= x_pos + w; x++) {
      if (x == x_pos || x == x_pos + w || y == y_pos || y == y_pos + h) {
        draw_pixel(x, y, stroke);
      } else {
        draw_pixel(x, y, color);
      }

    }
  }
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
