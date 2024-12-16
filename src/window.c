/*
 * Window management.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <GLFW/glfw3.h>
#include "context.h"
#include "log.h"
#include "renderer.h"
#include "window.h"

GLFWwindow *window = NULL;

static void
error_callback(int code, const char *description)
{
    error("GLFW error 0x%x: %s\n", code, description);
}

void
window_shutdown(void)
{
    debug("Shutting down window...\n");

    if (window != NULL) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void
window_loop(void)
{
    debug("Starting event/render loop...\n");

    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool
window_init(int width, int height, const char *title)
{
    debug("Initializing window...\n");

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        error("Failed to initialize GLFW\n");
        return false;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, CONTEXT_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CONTEXT_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        error("Failed to create GLFW window\n");
        return false;
    }

    return true;
}
