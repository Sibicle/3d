#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "vector.h"

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

uint32_t colors[7];

extern int window_width;
extern int window_height;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern SDL_Texture* color_buffer_texture;
extern uint32_t* color_buffer;

extern int previous_frame_time;

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

extern int      box_x;
extern int      box_y;
extern int      box_w;
extern int      box_h;
extern int      box_speed;
extern uint32_t box_stroke;

bool initialize_window(void);
void destroy_window(void);

void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void draw_pixel(int x, int y, uint32_t color);

void draw_grid(int spacing, int size, uint32_t color);
void draw_dots(int spacing, uint32_t color);
void draw_rect(int x_pos, int y_pos, int w, int h, uint32_t color, uint32_t stroke);

#endif
