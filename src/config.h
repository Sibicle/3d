#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>

#define DEBUG_MODE          false

#define RENDER_CAMERA_RAY   false

#define RENDER_ORIGIN       false

#define RENDER_LINES        true
#define RENDER_FACES        true
#define RENDER_VERTICES     false
#define RENDER_CENTROIDS    false
#define RENDER_NORMALS      false
#define RENDER_COLORS       false

#define CULL_NO_FACES       0
#define CULL_FRONT_FACES    1
#define CULL_BACK_FACES     2

#define MOVE_CAMERA_W_MOUSE false

extern bool render_camera_ray;

extern bool render_origin;

extern bool render_lines;
extern bool render_faces;
extern bool render_vertices;
extern bool render_centroids;
extern bool render_normals;
extern bool render_colors;

extern int cull_faces;

extern bool move_camera_w_mouse;

#endif
