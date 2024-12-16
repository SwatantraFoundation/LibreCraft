/*
 * Shader program utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _SHADER_H
#define _SHADER_H

#include <glad.h>

GLint get_uniform_location(GLuint program, const GLchar *name);
GLuint compile_shader(GLenum type, const char *source);
GLuint link_shader_program(const char *vert_source, const char *frag_source);
GLuint load_shader_program(const char *vert_filename, const char *frag_filename);

#endif /* !_SHADER_H */
