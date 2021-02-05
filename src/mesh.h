#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

typedef struct {
  vec3_t* vertices;
  face_t* faces;
  vec3_t* normals;
  vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

extern triangle_t* projected_triangles;
extern vec2_t* projected_normals;

void load_obj(char* filename);

#endif
