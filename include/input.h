#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

#include "util.h"
#include "display.h"

extern int mouse_x;
extern int mouse_y;

void process_input(void);

#endif
