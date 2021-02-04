#include "mesh.h"
#include "array.h"

mesh_t mesh = {
    .vertices = 0,
    .faces = 0,
    .rotation = { 0, 0, 0 }
};

vec3_t cube_vertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 },
    { .x = -1, .y =  1, .z = -1 },
    { .x =  1, .y =  1, .z = -1 },
    { .x =  1, .y = -1, .z = -1 },
    { .x =  1, .y =  1, .z =  1 },
    { .x =  1, .y = -1, .z =  1 },
    { .x = -1, .y =  1, .z =  1 },
    { .x = -1, .y = -1, .z =  1 }
};

face_t cube_faces[N_CUBE_FACES] = {
    // front
    { .a = 0, .b = 1, .c = 2 },
    { .a = 0, .b = 2, .c = 3 },
    // right
    { .a = 3, .b = 2, .c = 4 },
    { .a = 3, .b = 4, .c = 5 },
    // back
    { .a = 5, .b = 4, .c = 6 },
    { .a = 5, .b = 6, .c = 7 },
    // left
    { .a = 7, .b = 6, .c = 1 },
    { .a = 7, .b = 1, .c = 0 },
    // top
    { .a = 1, .b = 6, .c = 4 },
    { .a = 1, .b = 4, .c = 2 },
    // bottom
    { .a = 5, .b = 7, .c = 0 },
    { .a = 5, .b = 0, .c = 3 }
};

triangle_t* projected_triangles = 0;

void load_cube_mesh() {
  for(int i = 0; i < N_CUBE_VERTICES; i++) {
    vec3_t mesh_vertex = cube_vertices[i];
    array_push(mesh.vertices, mesh_vertex);
  }

  for(int j = 0; j < N_CUBE_FACES; j++) {
    face_t mesh_face = cube_faces[j];
    array_push(mesh.faces, mesh_face);
  }
}
