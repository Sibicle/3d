#include "vars.h"
#include "vector.h"

bool is_running = false;

float fov_factor = 640;

vec3_t cube_velocity = {
  .x = 0,
  .y = 0,
  .z = 0
};

vec3_t cube_rotation = {
  .x = 0,
  .y = 0,
  .z = 0
};
