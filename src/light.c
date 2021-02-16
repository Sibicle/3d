#include "light.h"

light_t global_light = {
  .orientation = {
    .x =  0.0,
    .y = -1.0,
    .z =  0.0
  }
};

color_t light_apply_intensity(color_t original, float percent) {
  color_t a = (original & 0xFF000000);
  color_t r = (original & 0x00FF0000) * percent;
  color_t g = (original & 0x0000FF00) * percent;
  color_t b = (original & 0x000000FF) * percent;

  color_t new = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);

  return new;
}
