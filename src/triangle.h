#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdint.h>

#include "vector.h"
#include "texture.h"

typedef uint32_t color_t;

typedef struct {
  int a;
  int b;
  int c;
  int a_uv;
  int b_uv;
  int c_uv;
  color_t color;
} face_t;

typedef struct {
  vec4_t points[3];
  vec4_t centroid;
  vec4_t normal;

  tex2_t uvs[3];

  float average_depth;

  color_t color;
} triangle_t;

int compare_z_depth(const void * a, const void * b);
void sort_triangles_by_depth(triangle_t * a);

void draw_filled_triangle(
  int x0, int y0,
  int x1, int y1,
  int x2, int y2,
  color_t color
);

void fill_flat_bottom_triangle(
  int x0, int y0,
  int x1, int y1,
  int x2, int y2,
  color_t color
);

void fill_flat_top_triangle(
  int x0, int y0,
  int x1, int y1,
  int x2, int y2,
  color_t color
);

#endif
