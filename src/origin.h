#ifndef ORIGIN_H
#define ORIGIN_H

#include <stdbool.h>

#include "vector.h"

extern vec3_t origin;
extern vec3_t x_axis;
extern vec3_t y_axis;
extern vec3_t z_axis;

void origin_render(void);
void mesh_origin_render(void);

#endif
