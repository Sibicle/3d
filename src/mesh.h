#ifndef MESH_H
#define MESH_H

typedef struct {
  float a;
  float b;
  float c;
} face_t;

#define GRID_GRID 0
#define GRID_DOT  1

extern int grid_size;
extern int grid_spacing;
extern int grid_type;

#endif
