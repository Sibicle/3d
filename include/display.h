#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "vector.h"
#include "triangle.h"
#include "matrix.h"

#define NUM_COLORS 7

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

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

extern color_t colors[7];

extern bool is_running;

extern int window_width;
extern int window_height;

extern vec2_t window_center;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern SDL_Texture* color_buffer_texture;
extern color_t* color_buffer;

extern int previous_frame_time;

extern mat4_t proj_matrix;

extern triangle_t * projected_triangles;

bool initialize_window(void);
void destroy_window(void);

void render_color_buffer(void);
void clear_color_buffer(color_t color);
void draw_pixel(int x, int y, color_t color);
void draw_texel(
  int x, int y, color_t * texture,
  vec4_t * a, vec4_t * b, vec4_t * c,
  float u2, float v2, float u1, float v1, float u0, float v0
);

mat4_t mat4_make_screen_matrix();

void draw_grid(int spacing, int size, color_t color);
void draw_dots(int spacing, color_t color);
void draw_rect(int x_pos, int y_pos, int w, int h, color_t color, color_t stroke);
void draw_line(int x0, int y0, int x1, int y1, color_t stroke);
void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t stroke);

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

#endif
