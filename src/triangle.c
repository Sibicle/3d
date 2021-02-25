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

vec3_t barycentric_weights(vec2_t * a, vec2_t * b, vec2_t * c, vec2_t * p) {
  vec2_t ab = vec2_sub(*b, *a);
  vec2_t bc = vec2_sub(*c, *b);
  vec2_t ac = vec2_sub(*c, *a);
  vec2_t ap = vec2_sub(*p, *a);
  vec2_t bp = vec2_sub(*p, *b);

  float area_abc = fabs(vec2_cross(&ac, &ab));
  float alpha    = fabs(vec2_cross(&bc, &bp) / area_abc);
  float beta     = fabs(vec2_cross(&ac, &ap) / area_abc);
float gamma    = 1 - alpha - beta;

  vec3_t weights = { alpha, beta, gamma };
  return weights;
}

tex2_t barycentric_uv_coords(
  float u_a, float v_a, float u_b, float v_b, float u_c, float v_c,
  vec3_t * weights
) {
  float alpha = weights->x;
  float beta  = weights->y;
  float gamma = weights->z;

  tex2_t uv = {
    .u = u_a * alpha + u_b * beta + u_c * gamma,
    .v = v_a * alpha + v_b * beta + v_c * gamma
  };

  return uv;
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
    swapf(&v0, &v1);
    swapf(&u0, &u1);
  }
  if (y1 > y2) {
    swapi(&y1, &y2);
    swapi(&x1, &x2);
    swapf(&v1, &v2);
    swapf(&u1, &u2);
  }
  if (y0 > y1) {
    swapi(&y0, &y1);
    swapi(&x0, &x1);
    swapf(&v0, &v1);
    swapf(&u0, &u1);
  }

  vec2_t a = { x2, y2 };
  vec2_t b = { x1, y1 };
  vec2_t c = { x0, y0 };

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
        vec2_t p       = { x, y };
        vec3_t weights = barycentric_weights(&a, &b, &c, &p);
        tex2_t uv      = barycentric_uv_coords(u2, v2, u1, v1, u0, v0, &weights);

        draw_texel(x, y, uv, texture);
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
        vec2_t p       = { x, y };
        vec3_t weights = barycentric_weights(&a, &b, &c, &p);
        tex2_t uv      = barycentric_uv_coords(u2, v2, u1, v1, u0, v0, &weights);

        draw_texel(x, y, uv, texture);
      }
    }
  }
}
