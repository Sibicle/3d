#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

typedef struct {
  vec3_t* vertices;
  face_t* faces;
  vec3_t r;
  vec3_t v_r;
} mesh_t;

extern mesh_t mesh;
extern mesh_t cube;

extern triangle_t* projected_triangles;

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

#endif
