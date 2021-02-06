#ifndef MESH_H
#define MESH_H

#define RENDER_FACES      true
#define RENDER_VERTICES   false
#define RENDER_CENTROIDS  false
#define RENDER_NORMALS    false
#define RENDER_BACK_FACES false

#include <stdbool.h>

#include "vector.h"
#include "triangle.h"

typedef struct {
  vec3_t * vertices;
  face_t * faces;
  vec3_t * normals;
  vec3_t * centroids;
  vec3_t rotation;
  vec3_t position;
} mesh_t;

extern mesh_t mesh;

extern triangle_t * projected_triangles;
extern vec2_t * projected_normals;
extern vec2_t * projected_centroids;

extern bool render_faces;
extern bool render_vertices;
extern bool render_centroids;
extern bool render_normals;
extern bool render_back_faces;

void load_obj(char * filename);

void calculate_centroids_normals();

void transform_mesh(vec3_t translate, vec3_t rotate, vec3_t scale);
void translate_mesh(vec3_t translate);
void rotate_mesh(vec3_t rotate);
void scale_mesh(vec3_t scale);
void scale_mesh_uniform(float scale);

void free_mesh();

#endif
