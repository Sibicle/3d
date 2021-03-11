#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "display.h"

typedef struct {
  vec3_t orientation;
} light_t;

light_t global_light;

color_t light_apply_intensity(color_t original, float percent);

#endif
