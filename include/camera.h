/*
 * Perspective camera.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _CAMERA_H
#define _CAMERA_H

#include <glad.h>
#include <stdbool.h>
#include "mat4.h"

struct camera {
    mat4_t proj;
    mat4_t view;
};

/*
 * Frees resources allocated for cam.
 */
void camera_destroy(struct camera *cam);

/*
 * Translates cam by (x, y, z).
 */
void camera_translate(struct camera *cam, float x, float y, float z);

/*
 * Translates cam to (0, 0, 0) and
 * rotates it by (x, y, z) radians.
 */
void camera_rotate(struct camera *cam, float x, float y, float z);

/*
 * Loads cam's projection and view
 * matrices into the shader program.
 * This must be done before rendering.
 */
void camera_load(struct camera *cam, GLint proj_location, GLint view_location);

/*
 * Initializes cam with a given
 * field of view and aspect ratio.
 */
bool camera_init(struct camera *cam, float fov, float aspect);

#endif /* !_CAMERA_H */
