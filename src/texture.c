/*
 * Texture management utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include "log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"

GLuint
load_texture_array(const char *filename)
{
    int width, height, channels;
    void *data;
    GLuint tex;

    debug("Loading texture \"%s\" as array...\n", filename);

    data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL) {
        error("Failed to load \"%s\"\n");
        return 0;
    }

    /* Create and setup texture */
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Send texture data to GPU */
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, width, 16, height / 16, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    return tex;
}
