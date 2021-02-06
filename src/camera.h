#ifndef CAMERA_H
#define CAMERA_H

#include <stdbool.h>

#include "vector.h"

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define RENDER_CAMERA_RAY true

float fov_factor;
vec3_t camera_pos;
vec2_t projected_camera_pos;
bool render_camera_ray;

vec2_t project(vec3_t point);
void camera_ray_render(void);

#endif
