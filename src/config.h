#ifndef CONFIG_H
#define CONFIG_H

typedef enum {

  DEBUG_MODE       = (1 << 1),

  RENDER_LINES     = (1 << 2),
  RENDER_FACES     = (1 << 3),
  RENDER_COLORS    = (1 << 4),
  RENDER_LIGHTING  = (1 << 5),
  RENDER_TEXTURES  = (1 << 6),

  CULL_FRONT_FACES = (1 << 7),
  CULL_BACK_FACES  = (1 << 8),

  SHOW_VERTICES    = (1 << 9),
  SHOW_NORMALS     = (1 << 10),
  SHOW_CENTROIDS   = (1 << 11),

  SHOW_ORIGIN      = (1 << 12),
  SHOW_CAMERA_RAY  = (1 << 13)

} FLAGS;

#define FLAGS_TEXTURED         RENDER_FACES           \
                             | RENDER_TEXTURES        \
                             | CULL_BACK_FACES

#define FLAGS_SHADED           RENDER_FACES           \
                             | RENDER_LIGHTING        \
                             | CULL_BACK_FACES

#define FLAGS_WIREFRAME        RENDER_LINES           \
                             | CULL_BACK_FACES

#define FLAGS_DEBUG_MATH       DEBUG_MODE             \
                             | RENDER_LINES           \
                             | SHOW_VERTICES          \
                             | SHOW_NORMALS           \
                             | SHOW_CENTROIDS         \
                             | SHOW_ORIGIN

#define FLAGS_DEBUG_SHADING    DEBUG_MODE             \
                             | RENDER_FACES           \
                             | RENDER_COLORS          \
                             | RENDER_LIGHTING        \
                             | SHOW_NORMALS

#define FLAGS_DEBUG_TEXTURES   DEBUG_MODE             \
                             | RENDER_FACES           \
                             | RENDER_TEXTURES



int flags;

#endif
