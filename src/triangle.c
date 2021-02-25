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

vec3_t barycentric_weights(vec4_t * a, vec4_t * b, vec4_t * c, vec4_t * p) {
  vec4_t ab = vec4_sub(b, a);
  vec4_t bc = vec4_sub(c, b);
  vec4_t ac = vec4_sub(c, a);
  vec4_t ap = vec4_sub(p, a);
  vec4_t bp = vec4_sub(p, b);

  vec4_t area_v  = vec4_cross(&ac, &ab);
  vec4_t alpha_v = vec4_cross(&bc, &bp);
  vec4_t beta_v  = vec4_cross(&ac, &ap);

  float area  = fabs(area_v.z);
  float alpha = fabs(alpha_v.z / area);
  float beta  = fabs(beta_v.z / area);
  float gamma = 1 - alpha - beta;

  vec3_t weights = { alpha, beta, gamma };
  return weights;
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
  int x0, int y0, float z0, float w0, float u0, float v0,
  int x1, int y1, float z1, float w1, float u1, float v1,
  int x2, int y2, float z2, float w2, float u2, float v2,
  color_t * texture
) {
  if (y0 > y1) {
    swapi(&x0, &x1);
    swapi(&y0, &y1);
    swapf(&z0, &z1);
    swapf(&w0, &w1);
    swapf(&v0, &v1);
    swapf(&u0, &u1);
  }
  if (y1 > y2) {
    swapi(&x1, &x2);
    swapi(&y1, &y2);
    swapf(&z1, &z2);
    swapf(&w1, &w2);
    swapf(&v1, &v2);
    swapf(&u1, &u2);
  }
  if (y0 > y1) {
    swapi(&x0, &x1);
    swapi(&y0, &y1);
    swapf(&z0, &z1);
    swapf(&w0, &w1);
    swapf(&v0, &v1);
    swapf(&u0, &u1);
  }

  vec4_t a = { x2, y2, z2, w2 };
  vec4_t b = { x1, y1, z1, w1 };
  vec4_t c = { x0, y0, z0, w0 };

  if (y2 - y0 != 0) {
    float inv_slope_1 = 0;
    float inv_slope_2 = 0;

    if (y2 - y0 != 0) {
      inv_slope_1 = (float)(x2 - x0) / abs(y2 - y0);
    }

    if (y2 - y1 != 0) {
      inv_slope_2 = (float)(x2 - x1) / abs(y2 - y1);
    }

    for (int y = y2; y >= y1; y--) {
      int x_start = x0 + (y - y0) * inv_slope_1;
      int x_end   = x1 + (y - y1) * inv_slope_2;

      if (x_start > x_end) {
        swapi(&x_start, &x_end);
      }

      for (int x = x_start; x < x_end; x++) {
        draw_texel(x, y, texture, &a, &b, &c, u2, v2, u1, v1, u0, v0);
      }
    }

    if (y1 - y0 != 0) {
      inv_slope_2 = (float)(x1 - x0) / abs(y1 - y0);
    }

    for (int y = y1; y >= y0; y--) {
      int x_start = x0 + (y - y0) * inv_slope_1;
      int x_end   = x0 + (y - y0) * inv_slope_2;

      if (x_start > x_end) {
        swapi(&x_start, &x_end);
      }

      for (int x = x_start; x < x_end; x++) {
        draw_texel(x, y, texture, &a, &b, &c, u2, v2, u1, v1, u0, v0);
      }
    }
  }
}
