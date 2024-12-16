/*
 * Master renderer.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _RENDERER_H
#define _RENDERER_H

#include <stdbool.h>

void renderer_shutdown(void);
void render(void);
bool renderer_init(float fov, float aspect);

#endif /* !_RENDERER_H */
