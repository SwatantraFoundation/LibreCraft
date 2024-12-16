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

#define LC_VERSION "0.0.1"
#define LC_NAME    "LibreCraft v" LC_VERSION

#define WINDOW_TITLE  LC_NAME
#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

#define CONTEXT_VSYNC 1

#define PLAYER_FOV (70.0f * RAD_PER_DEG)

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    debug("Starting " LC_NAME "...\n");

    if (!window_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)) {
        return EXIT_FAILURE;
    }

    if (!context_init(WINDOW_WIDTH, WINDOW_HEIGHT, CONTEXT_VSYNC)) {
        window_shutdown();
        return EXIT_FAILURE;
    }

    if (!renderer_init(PLAYER_FOV, (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)) {
        window_shutdown();
        return EXIT_FAILURE;
    }

    /* Start the main loop */
    window_loop();

    /* Clean up */
    renderer_shutdown();
    window_shutdown();

    debug(LC_NAME " shut down successfully\n");
    return EXIT_SUCCESS;
}
