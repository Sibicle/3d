#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mesh.h"
#include "array.h"

mesh_t mesh = {
    .vertices = 0,
    .faces = 0,
    .normals = 0,
    .centroids = 0,
    .rotation = { 0, 0, 0 }
};

triangle_t* projected_triangles = 0;
vec2_t* projected_normals = 0;
vec2_t* projected_centroids = 0;

void parse_obj_line(char * line) {
  char l[256];

  strcpy(l, line);
  char delim[] = " \n";
	char *ptr = strtok(l, delim);

	while (ptr != NULL) {
    switch(*ptr) {
      case 'v':
      {
        char * x = strtok(NULL, delim);
        char * y = strtok(NULL, delim);
        char * z = strtok(NULL, delim);

        char * end;

        vec3_t vertex = {
          .x = strtod(x, &end),
          .y = strtod(y, &end),
          .z = strtod(z, &end)
        };

        array_push(mesh.vertices, vertex);
        break;
      }

      case 'f':
      {
        char * a = strtok(NULL, delim);
        char * b = strtok(NULL, delim);
        char * c = strtok(NULL, delim);

        char * end;

        face_t face = {
          .a = strtoimax(a, &end, 10),
          .b = strtoimax(b, &end, 10),
          .c = strtoimax(c, &end, 10)
        };

        array_push(mesh.faces, face);

        break;
      }
    }

		ptr = strtok(NULL, delim);
	}
}

void load_obj(char * filename) {
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
    transformed_vertex = vec3_scale(transformed_vertex, scale);
    transformed_vertex = vec3_rotate(transformed_vertex, rotate);

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
