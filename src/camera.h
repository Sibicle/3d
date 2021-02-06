#ifndef CAMERA_H
#define CAMERA_H

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#include <stdbool.h>

#include "vector.h"

float fov_factor;
vec3_t camera_pos;
vec2_t projected_camera_pos;

vec2_t project(vec3_t point);
void camera_ray_render(void);

void print_camera_pos(void);

#endif
