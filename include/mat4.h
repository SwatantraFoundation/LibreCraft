/*
 * 4x4 float matrix utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _MAT4_H
#define _MAT4_H

#define RAD_PER_DEG (3.14159265f / 180.0f)

#define SIZEOF_MAT4 (sizeof(float) * 16)
typedef float* mat4_t;

void mat4_perspective(mat4_t mat, float fovy, float aspect, float near, float far);
void mat4_rotate(mat4_t mat, float x, float y, float z);
void mat4_translate(mat4_t mat, float x, float y, float z);
void mat4_identity(mat4_t mat);

#endif /* !_MAT4_H */
