#ifndef VARS_H
#define VARS_H
#define N_POINTS (9 * 9 * 9)

#include <stdbool.h>

#include "vector.h"

bool is_running;

float fov_factor;
vec3_t camera_pos;

vec3_t cube_points [N_POINTS];
vec2_t projected_points [N_POINTS];

#endif
