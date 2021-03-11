#ifndef ORIGIN_H
#define ORIGIN_H

#include <stdbool.h>

#include "vector.h"

extern vec3_t origin;

extern vec3_t x_axis;
extern vec3_t y_axis;
extern vec3_t z_axis;

void show_origin(void);
void show_mesh_origin(void);

#endif
