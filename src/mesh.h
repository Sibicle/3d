#ifndef MESH_H
#define MESH_H

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

#include "vector.h"
#include "triangle.h"

typedef struct {
  vec3_t* vertices;
  face_t* faces;
  vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

extern triangle_t* projected_triangles;

void load_cube_mesh();

#endif
