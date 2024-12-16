/*
 * Perspective camera.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <glad.h>
#include <stddef.h>
#include <stdlib.h>
#include "camera.h"
#include "log.h"
#include "mat4.h"

void
camera_destroy(struct camera *cam)
{
    debug("Destroying camera...\n");

    if (cam->view != NULL) {
        free(cam->view);
    }

    if (cam->proj != NULL) {
        free(cam->proj);
    }
}

void
camera_translate(struct camera *cam, float x, float y, float z)
{
    mat4_translate(cam->view, x, y, z);
}

void
camera_rotate(struct camera *cam, float x, float y, float z)
{
    mat4_identity(cam->view);
    mat4_rotate(cam->view, x, y, z);
}

void
camera_load(struct camera *cam, GLint proj_location, GLint view_location)
{
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, cam->proj);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, cam->view);
}

void
camera_init(struct camera *cam, float fov, float aspect)
{
	debug("Initializing camera...\n");

    cam->proj = malloc(SIZEOF_MAT4);
    cam->view = malloc(SIZEOF_MAT4);

    mat4_identity(cam->proj);
    mat4_identity(cam->view);

    mat4_perspective(cam->proj, fov, aspect, 0.01f, 1000.0f);
}
