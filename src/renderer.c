/*
 * Master renderer.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <glad.h>
#include <stdint.h>
#include "camera.h"
#include "log.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"

/* TODO: These will not always be constant */
#define N_VERTICES  4
#define N_INSTANCES 2

/* Shader program attribute locations */
#define ATTR_MODEL_POS       0
#define ATTR_MODEL_TEX_COORD 1
#define ATTR_INST_DATA       2

static GLuint program = 0;
static GLuint texture = 0;
static GLint proj_location, view_location;
static struct camera camera;

static float vertices[] = {
    -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f
};
static GLuint instances[N_INSTANCES] = {
    0x00000000,
    0x01010001
};
static GLuint vao, modelVbo, instVbo;

static void
create_buffers(void)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /* Create model data buffer */
    glGenBuffers(1, &modelVbo);
    glBindBuffer(GL_ARRAY_BUFFER, modelVbo);
    glBufferData(GL_ARRAY_BUFFER, N_VERTICES * 5 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(ATTR_MODEL_POS, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(ATTR_MODEL_POS);
    glVertexAttribPointer(ATTR_MODEL_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(ATTR_MODEL_TEX_COORD);

    /* Create instance data buffer */
    glGenBuffers(1, &instVbo);
    glBindBuffer(GL_ARRAY_BUFFER, instVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * N_INSTANCES, instances, GL_STATIC_DRAW);
    glVertexAttribIPointer(ATTR_INST_DATA, 1, GL_UNSIGNED_INT, 0, 0);
    glVertexAttribDivisor(ATTR_INST_DATA, 1);
    glEnableVertexAttribArray(ATTR_INST_DATA);
}

void
renderer_shutdown(void)
{
    debug("Shutting down renderer...\n");

    camera_destroy(&camera);

    if (texture) {
        glDeleteTextures(1, &texture);
        texture = 0;
    }

    if (program) {
        glDeleteProgram(program);
        program = 0;
    }
}

void
render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Setup shader program */
    glUseProgram(program);
    camera_load(&camera, proj_location, view_location);

    /* Bind block texture array */
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

    /* Bind & draw model */
    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, N_VERTICES, N_INSTANCES);
}

bool
renderer_init(float fov, float aspect)
{
    debug("Initializing renderer...\n");

    program = load_shader_program("res/world.vert", "res/world.frag");
    if (!program) {
        return false;
    }

    proj_location = get_uniform_location(program, "proj");
    if (proj_location < 0) {
        glDeleteProgram(program);
        return false;
    }

    view_location = get_uniform_location(program, "view");
    if (view_location < 0) {
        glDeleteProgram(program);
        return false;
    }

    texture = load_texture_array("res/blocks.png");
    if (!texture) {
        glDeleteProgram(program);
        return false;
    }

    if (!camera_init(&camera, fov, aspect)) {
        glDeleteProgram(program);
        return false;
    }

    camera_translate(&camera, 0.0f, -1.62f, 3.0f);

    create_buffers();

    return true;
}
