/*
 * Perspective camera.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <stddef.h>
#include <stdlib.h>
#include "camera.h"
#include "log.h"

void
camera_destroy(struct camera *cam)
{
    debug("Destroying camera...\n");

    if (cam->view != NULL) {
        free(cam->view);
        cam->view = NULL;
    }

    if (cam->proj != NULL) {
        free(cam->proj);
        cam->proj = NULL;
    }
}

void
camera_translate(struct camera *cam, float x, float y, float z)
{
    /* Apply translation to view matrix */
    mat4_translate(cam->view, x, y, z);
}

void
camera_rotate(struct camera *cam, float x, float y, float z)
{
    /* Apply rotation around (0, 0, 0) to view matrix */
    mat4_identity(cam->view);
    mat4_rotate(cam->view, x, y, z);
}

void
camera_load(struct camera *cam, GLint proj_location, GLint view_location)
{
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, cam->proj);
    glUniformMatrix4fv(view_location, 1, GL_FALSE, cam->view);
}

bool
camera_init(struct camera *cam, float fov, float aspect)
{
    debug("Initializing camera...\n");

    cam->proj = malloc(SIZEOF_MAT4);
    if (cam->proj == NULL) {
        error("Failed to allocate memory for camera projection matrix\n");
        return false;
    }

    cam->view = malloc(SIZEOF_MAT4);
    if (cam->view == NULL) {
        error("Failed to allocate memory for camera view matrix\n");
        free(cam->proj);
        return false;
    }

    /* Initialize matrices to identity */
    mat4_identity(cam->proj);
    mat4_identity(cam->view);

    /* Set perspective projection matrix */
    mat4_perspective(cam->proj, fov, aspect, 0.01f, 1000.0f);

    return true;
}
