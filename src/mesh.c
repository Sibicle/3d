#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "config.h"
#include "mesh.h"
#include "array.h"
#include "util.h"
#include "display.h"

mesh_t mesh = {
    .vertices = 0,
    .faces = 0,
    .normals = 0,
    .centroids = 0,
    .rotation = { 0, 0, 0 },
    .position = { 0, 0, 0 }
};

void parse_obj_line(char * line) {
  if (strncmp(line, "v ", 2) == 0) {
    vec3_t vertex;
    sscanf(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
    array_push(mesh.vertices, vertex);
  } else if (strncmp(line, "f ", 2) == 0) {
    int vertex_indices[3];
    int texture_indices[3];
    int normal_indices[3];

    int matches = sscanf(
      line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
      &vertex_indices[0], &texture_indices[0], &normal_indices[0],
      &vertex_indices[1], &texture_indices[1], &normal_indices[1],
      &vertex_indices[2], &texture_indices[2], &normal_indices[2]
    );

    if (matches != 9) {
      matches = sscanf(
        line, "f %d %d %d",
        &vertex_indices[0],
        &vertex_indices[1],
        &vertex_indices[2]
      );
    }

    int color_index = rand_int(0, NUM_COLORS - 1);
    uint32_t color = colors[color_index];

    face_t face = {
      .a = vertex_indices[0],
      .b = vertex_indices[1],
      .c = vertex_indices[2],
      .color = color
    };

    array_push(mesh.faces, face);
  }
}

void load_obj(char * filename) {
  free_mesh();

  mesh.vertices = 0;
  mesh.faces = 0;
  mesh.normals = 0;
  mesh.centroids = 0;

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

  calculate_centroids_normals();
}

void calculate_centroids_normals() {
  array_free(mesh.centroids);
  array_free(mesh.normals);

  mesh.centroids = 0;
  mesh.normals = 0;

  for(int i = 0; i < array_length(mesh.faces); i++) {
    face_t face = mesh.faces[i];

    vec3_t a = mesh.vertices[face.a - 1];
    vec3_t b = mesh.vertices[face.b - 1];
    vec3_t c = mesh.vertices[face.c - 1];

    vec3_t normal = tri_normal(a, b, c);

    array_push(mesh.normals, normal);

    vec3_t centroid = tri_centroid(a, b, c);

    array_push(mesh.centroids, centroid);
  }
}

void transform_mesh(vec3_t translate, vec3_t rotate, vec3_t scale) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_add(transformed_vertex, translate);
    transformed_vertex = vec3_rotate(transformed_vertex, rotate);
    transformed_vertex = vec3_scale(transformed_vertex, scale);

    mesh.vertices[i] = transformed_vertex;
  }

  calculate_centroids_normals();
}

void translate_mesh(vec3_t translate) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_add(transformed_vertex, translate);

    mesh.vertices[i] = transformed_vertex;
  }

  calculate_centroids_normals();
}

void rotate_mesh(vec3_t rotate) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_rotate(transformed_vertex, rotate);

    mesh.vertices[i] = transformed_vertex;
  }

  calculate_centroids_normals();
}

void scale_mesh(vec3_t scale) {
  for(int i = 0; i < array_length(mesh.vertices); i++) {
    vec3_t transformed_vertex = mesh.vertices[i];

    transformed_vertex = vec3_scale(transformed_vertex, scale);

    mesh.vertices[i] = transformed_vertex;
  }

  calculate_centroids_normals();
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

  calculate_centroids_normals();
}

void print_mesh_pos(void) {
  if (DEBUG_MODE) {
    char str[1024];
    vec3_to_string(str, mesh.position);
    printf("mesh: %s\n", str);
  }
}

void free_mesh() {
  array_free(mesh.vertices);
  array_free(mesh.faces);
  array_free(mesh.normals);
  array_free(mesh.centroids);
}
