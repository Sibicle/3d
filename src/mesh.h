#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)

extern vec3_t cube_vertices [N_CUBE_VERTICES];
extern face_t cube_faces [N_CUBE_FACES];

extern triangle_t* projected_triangles;

extern vec3_t mesh_rotation;
extern vec3_t mesh_velocity;

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

#endif
