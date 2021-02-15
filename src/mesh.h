#ifndef MESH_H
#define MESH_H

#include <stdbool.h>

#include "vector.h"
#include "triangle.h"
#include "matrix.h"

typedef struct {
  vec3_t * vertices;
  face_t * faces;
  vec3_t * normals;
  vec3_t * centroids;
  vec3_t rotation;
  vec3_t position;
  vec3_t scale;
} mesh_t;

extern mesh_t mesh;

void load_obj(char * filename);

void calculate_centroids_normals();

void transform_mesh(vec3_t translate, vec3_t rotate, vec3_t scale);
void translate_mesh(vec3_t translate);
void rotate_mesh(vec3_t rotate);
void scale_mesh(vec3_t scale);
void scale_mesh_uniform(float scale);

mat4_t mat4_make_world_matrix();

void print_mesh_pos(void);

void free_mesh();

#endif
