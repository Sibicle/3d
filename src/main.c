#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define BG      0x282A36
#define LINE    0x44475A
#define FG      0xF8F8F2
#define COMMENT 0x6272A4
#define CYAN    0x8BE9FD
#define GREEN   0x50FA7B
#define ORANGE  0xFFB86C
#define PINK    0xFF79C6
#define PURPLE  0xBD93F9
#define RED     0xFF5555
#define YELLOW  0xF1FA8C

bool is_running = false;

int window_width       = 800;
int window_height      = 600;

int grid_size          = 1;
int grid_spacing       = 10;

SDL_Window* window     = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer            = NULL;


void set_pixel(int x, int y, uint32_t color) {
  color_buffer[(window_width * y) + x] = color;
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

  return true;
}

void setup(void) {
  color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

  color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
  );
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch(event.type) {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        is_running = false;
      } else if (event.key.keysym.sym == SDLK_UP) {

      }
      break;
  }
}

void update(void) {
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
      set_pixel(x, y, color);
    }
  }
}

void draw_grid(int spacing, int size) {
  for(int y = 0; y < window_height; y++) {
    for(int x = 0; x < window_width; x++) {
      if(x % spacing < size) {
        set_pixel(x, y, LINE);
      }

      if(y % spacing < size) {
        set_pixel(x, y, LINE);
      }
    }
  }
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  draw_grid(grid_spacing, grid_size);

  render_color_buffer();

  clear_color_buffer(BG);

  SDL_RenderPresent(renderer);
}

void destroy_window(void) {
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
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

  return 0;
}
