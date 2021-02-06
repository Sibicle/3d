#include <string.h>
#include <stdio.h>
#include <math.h>

#include "mesh_files.h"
#include "mesh.h"
#include "array.h"

mesh_file * mesh_files = 0;
int mesh_index = -1;

void load_mesh_files() {
  mesh_file file;

  INIT_MESH_FILE(file, "cube.obj");
  array_push(mesh_files, file);

  INIT_MESH_FILE(file, "teapot.obj");
  file.rotate.x = M_PI;
  file.scale.x = 0.75;
  file.scale.y = 0.75;
  file.scale.z = 0.75;
  file.translate.y = 1;
  array_push(mesh_files, file);

  INIT_MESH_FILE(file, "f22.obj");
  file.rotate.x = M_PI;
  array_push(mesh_files, file);

  INIT_MESH_FILE(file, "bear.obj");
  file.rotate.x = M_PI;
  file.scale.x = 0.1;
  file.scale.y = 0.1;
  file.scale.z = 0.1;
  array_push(mesh_files, file);

  INIT_MESH_FILE(file, "cow.obj");
  file.rotate.x = M_PI;
  file.scale.x = 0.5;
  file.scale.y = 0.5;
  file.scale.z = 0.5;
  array_push(mesh_files, file);

  // INIT_MESH_FILE(file, "pumpkin.obj");
  // file.scale.x = 0.5;
  // file.scale.y = 0.5;
  // file.scale.z = 0.5;
  // array_push(mesh_files, file);
}

void load_next_mesh_file() {
  mesh_index = (mesh_index + 1) % array_length(mesh_files);

  mesh_file file = mesh_files[mesh_index];

  char path[1024] = "assets/";
  strcat(path, file.filename);

  printf("loading mesh '%s'\n", file.filename);

  load_obj(path);
  transform_mesh(file.translate, file.rotate, file.scale);
}

void free_mesh_files() {
  array_free(mesh_files);
}
