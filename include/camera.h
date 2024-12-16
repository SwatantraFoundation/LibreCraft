/*
 * Perspective camera.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _CAMERA_H
#define _CAMERA_H

#include "mat4.h"

struct camera {
    mat4_t proj;
    mat4_t view;
};

void camera_destroy(struct camera *cam);
void camera_translate(struct camera *cam, float x, float y, float z);
void camera_rotate(struct camera *cam, float x, float y, float z);
void camera_load(struct camera *cam, GLint proj_location, GLint view_location);
void camera_init(struct camera *cam, float fov, float aspect);

#endif /* !_CAMERA_H */
