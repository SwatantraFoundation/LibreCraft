/*
 * LibreCraft main entry point.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <stdlib.h>
#include "context.h"
#include "log.h"
#include "mat4.h"
#include "renderer.h"
#include "window.h"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define PLAYER_FOV (70.0f * RAD_PER_DEG)

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    debug("LibreCraft v0.0.1\n");

    if (!window_init(WINDOW_WIDTH, WINDOW_HEIGHT, "LibreCraft")) {
        return EXIT_FAILURE;
    }

    if (!context_init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        return EXIT_FAILURE;
    }

    if (!renderer_init(PLAYER_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)) {
        return EXIT_FAILURE;
    }

    window_loop();

    renderer_shutdown();
    window_shutdown();
    return EXIT_SUCCESS;
}
