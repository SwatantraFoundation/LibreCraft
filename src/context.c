/*
 * Context creation and setup.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <glad.h>
#include <GLFW/glfw3.h>
#include "context.h"
#include "log.h"

extern GLFWwindow *window;

bool
context_init(int width, int height, int vsync)
{
    debug("Initializing context...\n");

    if (window == NULL) {
        error("Failed to initialize context: window is NULL\n");
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(vsync);

    /* Load OpenGL symbols */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        error("Failed to load OpenGL with GLAD\n");
        return false;
    }

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    return true;
}
