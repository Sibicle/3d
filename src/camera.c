#include <stdio.h>

#include "config.h"
#include "camera.h"
#include "origin.h"
#include "display.h"
#include "vector.h"

float fov_factor = 640;
vec4_t camera_pos = { .x = 0.0, .y = 0.0, .z = -5.0, .w = 1.0 };
vec2_t projected_camera_pos = { .x = 0, .y = 0 };

void print_camera_pos(void) {
  if (DEBUG_MODE) {
    char str[1024];
    vec4_to_string(str, &camera_pos);
    printf("camera: %s\n", str);
  }
}
