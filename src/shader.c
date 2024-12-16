/*
 * Shader program utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "shader.h"

static char *
load_source(const char *filename)
{
    FILE *fp;
    size_t size;
    char* buf;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror(filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    size = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (size < 1) {
        fclose(fp);
        return NULL;
    }

    buf = malloc(size + 1);
    if (fread(buf, 1, size, fp) != size) {
        free(buf);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    buf[size] = '\0';
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
        glGetShaderInfoLog(shader, log_len, NULL, log);
        error("Failed to compile shader: %s\n", log);
        free(log);

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

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        GLsizei log_len;
        GLchar *log;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
        log = malloc(log_len + 1);
        glGetProgramInfoLog(program, log_len, NULL, log);
        error("Failed to link shader program: %s\n", log);
        free(log);

        glDeleteProgram(program);
        glDeleteShader(frag_shader);
        glDeleteShader(vert_shader);
        return 0;
    }

    glDetachShader(program, frag_shader);
    glDetachShader(program, vert_shader);

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
