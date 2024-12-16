/*
 * Shader program utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "shader.h"

static char *
load_source(const char *filename)
{
    FILE *fp;
    long size;
    char* buf;

    /* Open the file */
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        error("Failed to open file \"%s\": %s\n", filename, strerror(errno));
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        error("Failed to seek to the end of file \"%s\": %s\n", filename, strerror(errno));
        fclose(fp);
        return NULL;
    }

    /* Get the position to determine the file's size */
    size = ftell(fp);
    if (size < 0) {
        error("Failed to get the size of file \"%s\": %s\n", filename, strerror(errno));
        fclose(fp);
        return NULL;
    }

    if (fseek(fp, 0, SEEK_SET) != 0) {
        error("Failed to rewind to the beginning of file \"%s\": %s\n", filename, strerror(errno));
        fclose(fp);
        return NULL;
    }

    /* Allocate enough space for file and NULL terminator */
    buf = malloc(size + 1);
    if (buf == NULL) {
        error("Failed to allocate buffer for file \"%s\"\n", filename);
        fclose(fp);
        return NULL;
    }

    if (fread(buf, 1, (size_t)size, fp) != (size_t)size) {
        error("Failed to read entirety of file \"%s\"\n", filename);
        free(buf);
        fclose(fp);
        return NULL;
    }

    /* Terminate the buffer */
    buf[size] = '\0';

    fclose(fp);
    return buf;
}

GLint
get_uniform_location(GLuint program, const GLchar *name)
{
    GLint location;

    location = glGetUniformLocation(program, name);
    if (location < 0) {
        error("Failed to get location of uniform \"%s\"\n", name);
        return location;
    }

    return location;
}

GLuint
compile_shader(GLenum type, const char *source)
{
    GLuint shader;
    int status;

    shader = glCreateShader(type);
    if (!shader) {
        error("Failed to create shader of type %d\n", type);
        return 0;
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLsizei log_len;
        GLchar *log;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        log = malloc(log_len + 1);
        if (log == NULL) {
            error("Failed to compile shader\n");
            glDeleteShader(shader);
            return 0;
        }

        glGetShaderInfoLog(shader, log_len, NULL, log);
        error("Failed to compile shader: %s\n", log);
        free(log);

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint
link_shader_program(const char *vert_source, const char *frag_source)
{
    GLuint vert_shader, frag_shader;
    GLuint program;
    int status;

    vert_shader = compile_shader(GL_VERTEX_SHADER, vert_source);
    if (!vert_shader) {
        return 0;
    }

    frag_shader = compile_shader(GL_FRAGMENT_SHADER, frag_source);
    if (!frag_shader) {
        glDeleteShader(vert_shader);
        return 0;
    }

    program = glCreateProgram();
    if (!program) {
        error("Failed to create shader program\n");
        glDeleteShader(frag_shader);
        glDeleteShader(vert_shader);
        return 0;
    }

    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);

    /* Link program and delete unneeded individual shaders */
    glLinkProgram(program);
    glDetachShader(program, frag_shader);
    glDetachShader(program, vert_shader);
    glDeleteShader(frag_shader);
    glDeleteShader(vert_shader);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        GLsizei log_len;
        GLchar *log;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        log = malloc(log_len + 1);
        if (log == NULL) {
            error("Failed to link shader program\n");
            glDeleteProgram(program);
            return 0;
        }

        glGetProgramInfoLog(program, log_len, NULL, log);
        error("Failed to link shader program: %s\n", log);
        free(log);

        glDeleteProgram(program);
        return 0;
    }

    return program;
}

GLuint
load_shader_program(const char *vert_filename, const char *frag_filename)
{
    char *vert_source, *frag_source;
    GLuint program;

    debug("Loading shader program...\n");

    vert_source = load_source(vert_filename);
    if (vert_source == NULL) {
        return 0;
    }

    frag_source = load_source(frag_filename);
    if (frag_source == NULL) {
        free(vert_source);
        return 0;
    }

    program = link_shader_program(vert_source, frag_source);

    free(frag_source);
    free(vert_source);
    return program;
}
