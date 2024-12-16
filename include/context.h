/*
 * Context creation and setup.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _CONTEXT_H
#define _CONTEXT_H

#include <stdbool.h>

#define CONTEXT_VERSION_MAJOR 3
#define CONTEXT_VERSION_MINOR 3

bool context_init(int width, int height, int vsync);

#endif /* !_CONTEXT_H */
