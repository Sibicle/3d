#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mesh.h"

#include "config.h"
#include "array.h"
#include "util.h"
#include "display.h"
#include "texture.h"

mesh_t mesh = {
    .vertices = NULL,
    .faces    = NULL,
    .uvs      = NULL,
    .rotation = { 0.0, 0.0, 0.0 },
    .position = { 0.0, 0.0, 5.0 },
    .scale    = { 1.0, 1.0, 1.0 }
};

void mesh_init(void) {
  mesh = (mesh_t) {
    .vertices  = NULL,

    .faces     = NULL,
    .uvs       = NULL,

    .normals   = NULL,
    .centroids = NULL,

    .rotation  = { 0.0, 0.0, 0.0 },
    .position  = { 0.0, 0.0, 5.0 },
    .scale     = { 1.0, 1.0, 1.0 }
  };
}

void parse_obj_line(char * line) {
  if (strncmp(line, "v ", 2) == 0) {
    vec3_t vertex;
    sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
    array_push(mesh.vertices, vertex);
  } else if (strncmp(line, "vt ", 2) == 0) {
    tex2_t uv;
    sscanf(line, "vt %f %f", &uv.u, &uv.v);
    array_push(mesh.uvs, uv);
  } else if (strncmp(line, "f ", 2) == 0) {
    face_t face = { 0 };

    int normal[3];

    int matches = sscanf(
      line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
      &face.a, &face.a_uv, &normal[0],
      &face.b, &face.b_uv, &normal[1],
      &face.c, &face.c_uv, &normal[2]
    );

    if (matches != 9) {
      matches = sscanf(
        line, "f %d/%d %d/%d %d/%d",
        &face.a, &face.a_uv,
        &face.b, &face.b_uv,
        &face.c, &face.c_uv
      );
    }

    if (matches != 6) {
      sscanf(
        line, "f %d %d %d",
        &face.a,
        &face.b,
        &face.c
      );
    }

    int color_index = rand_int(0, NUM_COLORS - 1);
    face.color = colors[color_index];

    array_push(mesh.faces, face);
  }
}

void load_obj(char * filename) {

  free_mesh();
  mesh_init();

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(filename, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &len, fp)) != -1) {
    parse_obj_line(line);
  }

  fclose(fp);

  if (line)
    free(line);
}


void transform_mesh(vec3_t translate, vec3_t rotate, vec3_t scale) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_add(transformed_vertex, translate);
    transformed_vertex = vec3_rotate(transformed_vertex, rotate);
    transformed_vertex = vec3_scale(transformed_vertex, scale);

    mesh.vertices[i] = transformed_vertex;
  }
}

void translate_mesh(vec3_t translate) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_add(transformed_vertex, translate);

    mesh.vertices[i] = transformed_vertex;
  }
}

void rotate_mesh(vec3_t rotate) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_rotate(transformed_vertex, rotate);

    mesh.vertices[i] = transformed_vertex;
  }
}

void scale_mesh(vec3_t scale) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_scale(transformed_vertex, scale);

    mesh.vertices[i] = transformed_vertex;
  }
}

void scale_mesh_uniform(float scale) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];
    vec3_t s = {
      .x = scale,
      .y = scale,
      .z = scale
    };

    transformed_vertex = vec3_scale(transformed_vertex, s);

    mesh.vertices[i] = transformed_vertex;
  }
}

mat4_t mat4_make_world_matrix() {
  mat4_t world_matrix    = mat4_make_identity();

  mat4_t scale_matrix    = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
  mat4_t rotate_x_matrix = mat4_make_rotate_x(mesh.rotation.x);
  mat4_t rotate_y_matrix = mat4_make_rotate_y(mesh.rotation.y);
  mat4_t rotate_z_matrix = mat4_make_rotate_z(mesh.rotation.z);
  mat4_t trans_matrix    = mat4_make_trans(mesh.position.x, mesh.position.y, mesh.position.z);

  mat4_mul_mat4(&world_matrix, &trans_matrix);
  mat4_mul_mat4(&world_matrix, &rotate_x_matrix);
  mat4_mul_mat4(&world_matrix, &rotate_y_matrix);
  mat4_mul_mat4(&world_matrix, &rotate_z_matrix);
  mat4_mul_mat4(&world_matrix, &scale_matrix);

  return world_matrix;
}

void mesh_print_pos(void) {
  char str[1024];
  vec3_to_string(str, &mesh.position);
  printf("mesh: %s\n", str);
}

void mesh_print(void) {
  for(int i = 0; i < array_length(mesh.faces); i++) {
    face_t face = mesh.faces[i];

    vec3_t va   = mesh.vertices[face.a - 1];
    vec3_t vb   = mesh.vertices[face.b - 1];
    vec3_t vc   = mesh.vertices[face.c - 1];

    tex2_t ta   = mesh.uvs[face.a_uv - 1];
    tex2_t tb   = mesh.uvs[face.b_uv - 1];
    tex2_t tc   = mesh.uvs[face.c_uv - 1];

    printf(
      "a: %d (% 4.2f, % 4.2f, % 4.2f), b: %d (% 4.2f, % 4.2f, % 4.2f), c: %d (% 4.2f, % 4.2f, % 4.2f)\n"
      "uva: {% 4.2f, % 4.2f},        uvb: {% 4.2f, % 4.2f},        uvc: {% 4.2f, % 4.2f}\n\n",
      face.a, va.x, va.y, va.z,      face.b, vb.x, vb.y, vb.z,     face.c, vc.x, vc.y, vc.z,
      ta.u, ta.v,                    tb.u, tb.v,                   tc.u, tc.v
    );
  }
}

void free_mesh(void) {
  array_free(mesh.vertices);
  array_free(mesh.faces);
  array_free(mesh.uvs);
}
