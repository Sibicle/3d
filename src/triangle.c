#include "triangle.h"
#include "util.h"
#include "display.h"
#include "array.h"
#include "light.h"

int compare_z_depth(const void * a, const void  * b) {
  triangle_t *a1 = (triangle_t *)a;
  triangle_t *b1 = (triangle_t *)b;

  if (a1->average_depth > b1->average_depth) return -1;
  if (a1->average_depth < b1->average_depth) return 1;

  return 0;
}

void sort_triangles_by_depth(triangle_t * a) {
  qsort(a, array_length(a), sizeof a[0], compare_z_depth);
}

void draw_filled_triangle(
  int x0, int y0, int x1, int y1, int x2, int y2,
  color_t color
) {
  if (y0 > y1) {
    swapi(&y0, &y1);
    swapi(&x0, &x1);
  }
  if (y1 > y2) {
    swapi(&y1, &y2);
    swapi(&x1, &x2);
  }
  if (y0 > y1) {
    swapi(&y0, &y1);
    swapi(&x0, &x1);
  }

  if (y1 == y2) {
    fill_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
  } else if (y0 == y1) {
    fill_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
  } else {
    int ym = y1;
    int xm = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

    fill_flat_top_triangle(x0, y0, x1, y1, xm, ym, color);
    fill_flat_bottom_triangle(x1, y1, xm, ym, x2, y2, color);
  }
}

void fill_flat_top_triangle(
  int x0, int y0, int x1, int y1, int x2, int y2,
  color_t color
) {
  float slope_1 = (float)(x0 - x1) / (y0 - y1);
  float slope_2 = (float)(x0 - x2) / (y0 - y2);

  float x_start = x0;
  float x_end   = x0;

  for (int y = y0; y <= y2; y++) {
    draw_line(x_start, y, x_end, y, color);
    x_start += slope_1;
    x_end   += slope_2;
  }
}

void fill_flat_bottom_triangle(
  int x0, int y0, int x1, int y1, int x2, int y2,
  color_t color
) {
  float slope_1 = (float)(x2 - x0) / (y2 - y0);
  float slope_2 = (float)(x2 - x1) / (y2 - y1);

  float x_start = x2;
  float x_end = x2;

  for (int y = y2; y >= y0; y--) {
    draw_line(x_start, y, x_end, y, color);
    x_start -= slope_1;
    x_end   -= slope_2;
  }
}
void draw_textured_triangle(
  int x0,   int y0,   int x1,   int y1,   int x2,   int y2,
  float u0, float v0, float u1, float v1, float u2, float v2,
  color_t * texture
) {
  if (y0 > y1) {
    swapi(&y0, &y1);
    swapi(&x0, &x1);
  }
  if (y1 > y2) {
    swapi(&y1, &y2);
    swapi(&x1, &x2);
  }
  if (y0 > y1) {
    swapi(&y0, &y1);
    swapi(&x0, &x1);
  }

  if (y1 == y2) {
    texture_flat_top_triangle(x0, y0, x1, y1, x2, y2, u0, v0, u1, v1, u2, v2, texture);
  } else if (y0 == y1) {
    texture_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, u0, v0, u1, v1, u2, v2, texture);
  } else {
    int ym = y1;
    int xm = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

    int vm = v1;
    int um = u0;

    texture_flat_top_triangle(x0, y0, x1, y1, xm, ym, u0, v0, u1, v1, um, vm, texture);
    texture_flat_bottom_triangle(x1, y1, xm, ym, x2, y2, u0, v0, um, vm, u2, v2, texture);
  }
}

void texture_flat_top_triangle(
  int x0,   int y0,   int x1,   int y1,   int x2,   int y2,
  float u0, float v0, float u1, float v1, float u2, float v2,
  color_t * texture
) {
  float slope_1 = (float)(x0 - x1) / (y0 - y1);
  float slope_2 = (float)(x0 - x2) / (y0 - y2);

  float x_start = x0;
  float x_end   = x0;

  for (int y = y0; y <= y2; y++) {
    draw_line(x_start, y, x_end, y, PURPLE);
    x_start += slope_1;
    x_end   += slope_2;
  }
}

void texture_flat_bottom_triangle(
  int x0,   int y0,   int x1,   int y1,   int x2,   int y2,
  float u0, float v0, float u1, float v1, float u2, float v2,
  color_t * texture
) {
  float slope_1 = (float)(x2 - x0) / (y2 - y0);
  float slope_2 = (float)(x2 - x1) / (y2 - y1);

  float x_start = x2;
  float x_end = x2;

  for (int y = y2; y >= y0; y--) {
    draw_line(x_start, y, x_end, y, PURPLE);
    x_start -= slope_1;
    x_end   -= slope_2;
  }
}
