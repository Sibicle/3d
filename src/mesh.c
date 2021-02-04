#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "mesh.h"
#include "array.h"

mesh_t mesh = {
    .vertices = 0,
    .faces = 0,
    .rotation = { 0, 0, 0 }
};

triangle_t* projected_triangles = 0;

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
  FILE *  fp;
  char *  line = NULL;
  size_t  len = 0;
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
