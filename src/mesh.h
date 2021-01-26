#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES (6 * 2)

extern vec3_t mesh_vertices [N_MESH_VERTICES];
extern face_t mesh_faces [N_MESH_FACES];

extern triangle_t projected_triangles [N_MESH_FACES];

extern vec3_t mesh_rotation;
extern vec3_t mesh_velocity;

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

#endif
