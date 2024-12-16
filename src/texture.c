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

    debug("Loading texture array \"%s\"...\n", filename);

    /* Load and decode the image */
    data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL) {
        error("Failed to load texture file \"%s\"\n");
        return 0;
    }

    /* Create texture and set parameters */
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /* Send texture data to GPU and generate mipmaps */
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB, width, 16, height / 16, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    /* Free texture data on CPU */
    stbi_image_free(data);
    return tex;
}
