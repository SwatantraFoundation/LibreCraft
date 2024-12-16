/*
 * Master renderer.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _RENDERER_H
#define _RENDERER_H

#include <stdbool.h>

/*
 * Frees resources allocated for the renderer.
 */
void renderer_shutdown(void);

/*
 * Renders a single frame to the window.
 */
void render(void);

/*
 * Initializes the renderer by loading
 * shaders, textures, and models.
 * Also sets up a camera with the specified
 * field of view and aspect ratio.
 */
bool renderer_init(float fov, float aspect);

#endif /* !_RENDERER_H */
