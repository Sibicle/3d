#ifndef VARS_H
#define VARS_H

#include <stdbool.h>
#include "vector.h"

#define N_POINTS (9 * 9 * 9)
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

bool is_running;

float fov_factor;
vec3_t camera_pos;

vec3_t cube_points [N_POINTS];
vec2_t projected_points [N_POINTS];

vec3_t cube_velocity;
vec3_t cube_rotation;

#endif
