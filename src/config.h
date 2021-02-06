#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#define DEBUG_MODE        false

#define RENDER_CAMERA_RAY false

#define RENDER_ORIGIN     false

#define RENDER_FACES      true
#define RENDER_VERTICES   false
#define RENDER_CENTROIDS  false
#define RENDER_NORMALS    false
#define RENDER_BACK_FACES false

extern bool render_camera_ray;

extern bool render_origin;

extern bool render_faces;
extern bool render_vertices;
extern bool render_centroids;
extern bool render_normals;
extern bool render_back_faces;

#endif
