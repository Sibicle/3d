#include <stdbool.h>

#include "display.h"

uint32_t colors[7] = { CYAN, GREEN, ORANGE, PINK, PURPLE, RED, YELLOW };

bool is_running        = false;

int window_width       = DEFAULT_WINDOW_WIDTH;
int window_height      = DEFAULT_WINDOW_HEIGHT;
int pixels             = DEFAULT_WINDOW_WIDTH * DEFAULT_WINDOW_HEIGHT;

vec2_t window_center = {
  .x = (DEFAULT_WINDOW_WIDTH / 2),
  .y = (DEFAULT_WINDOW_HEIGHT / 2)
};

SDL_Window* window     = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer            = NULL;

int previous_frame_time = 0;

triangle_t * projected_triangles = 0;
vec2_t * projected_normals = 0;
vec2_t * projected_centroids = 0;

void draw_pixel(int x, int y, uint32_t color) {
  if (x >= 0 && x < window_width && y>= 0 && y < window_height) {
    color_buffer[(window_width * (window_height - y - 1)) + x] = color;
  }
}

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "error initializing SDl");
    return false;
  }

  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);

  window_width  = display_mode.w;
  window_height = display_mode.h - 29;
  pixels        = window_width * window_height;

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

  window_center = (vec2_t) {
    .x = (window_width / 2),
    .y = (window_height / 2)
  };

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    fprintf(stderr, "error creating SDL renderer");
    return false;
  }

  // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  SDL_PumpEvents();

  return true;
}

void destroy_window(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
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

void draw_rect(int x, int y, int w, int h, uint32_t color, uint32_t stroke) {
  for(int i = y; i <= y + h; i++) {
    for(int j = x; j <= x + w; j++) {
      if (j == x || j == x + w || i == y || i == y + h) {
        draw_pixel(j, i, stroke);
      } else {
        draw_pixel(j, i, color);
      }
    }
  }
}

void draw_line(int x0, int y0, int x1, int y1, uint32_t stroke) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int step;

  if(abs(dx) >= abs(dy)) {
    step = abs(dx);
  } else {
    step = abs(dy);
  }

  float inc_x = dx / (float) step;
  float inc_y = dy / (float) step;

  float x = x0;
  float y = y0;

  int i = 1;

  while(i <= step) {
    draw_pixel(round(x), round(y), stroke);

    x += inc_x;
    y += inc_y;
    i += 1;
  }
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t stroke) {
  draw_line(x0, y0, x1, y1, stroke);
  draw_line(x1, y1, x2, y2, stroke);
  draw_line(x2, y2, x0, y0, stroke);
}

int grid_size    = 1;
int grid_spacing = 10;
int grid_type    = GRID_DOT;
