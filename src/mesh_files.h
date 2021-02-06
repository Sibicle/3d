#ifndef MESH_FILES_H
#define MESH_FILES_H

#define INIT_MESH_FILE(var, fname)             \
  (var) = (mesh_file) {                        \
    .filename = (fname),                       \
    .rotate = VEC3_ZERO,                       \
    .translate = VEC3_ZERO,                    \
    .scale = VEC3_ONE                          \
  };

#include "vector.h"

typedef struct mesh_file {
  char filename[1024];
  vec3_t rotate;
  vec3_t translate;
  vec3_t scale;
} mesh_file;

extern mesh_file * mesh_files;
extern int mesh_index;

void load_mesh_files();
void load_next_mesh_file();
void free_mesh_files();

#endif
