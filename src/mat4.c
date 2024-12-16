/*
 * 4x4 float matrix utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <math.h>
#include <string.h>
#include "mat4.h"

static float identity[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

void
mat4_perspective(mat4_t mat, float fovy, float aspect, float near, float far)
{
    float f, fn;

    f = 1.0f / tanf(fovy * 0.5f);
    fn = 1.0f / (near - far);

    mat[0] = f / aspect;
    mat[5] = f;
    mat[10] = -(near + far) * fn;
    mat[11] = 1.0f;
    mat[14] = 2.0f * near * far * fn;
    mat[15] = 0.0f;
}

void
mat4_rotate(mat4_t mat, float x, float y, float z)
{
    float cos_x, sin_x, cos_y, sin_y, a00, a01, a02, a03, a20, a21, a22, a23;

    (void)z;

    cos_x = cosf(x);
    sin_x = sinf(x);
    cos_y = cosf(y);
    sin_y = sinf(y);

    a00 = mat[4];
    a01 = mat[5];
    a02 = mat[6];
    a03 = mat[7];
    a20 = mat[8];
    a21 = mat[9];
    a22 = mat[10];
    a23 = mat[11];

    mat[4] = a00 * cos_x + a20 * sin_x;
    mat[5] = a01 * cos_x + a21 * sin_x;
    mat[6] = a02 * cos_x + a22 * sin_x;
    mat[7] = a03 * cos_x + a23 * sin_x;
    mat[8] = a20 * cos_x - a00 * sin_x;
    mat[9] = a21 * cos_x - a01 * sin_x;
    mat[10] = a22 * cos_x - a02 * sin_x;
    mat[11] = a23 * cos_x - a03 * sin_x;

    a00 = mat[0];
    a01 = mat[1];
    a02 = mat[2];
    a03 = mat[3];
    a20 = mat[8];
    a21 = mat[9];
    a22 = mat[10];
    a23 = mat[11];

    mat[0] = a00 * cos_y - a20 * sin_y;
    mat[1] = a01 * cos_y - a21 * sin_y;
    mat[2] = a02 * cos_y - a22 * sin_y;
    mat[3] = a03 * cos_y - a23 * sin_y;
    mat[8] = a00 * sin_y + a20 * cos_y;
    mat[9] = a01 * sin_y + a21 * cos_y;
    mat[10] = a02 * sin_y + a22 * cos_y;
    mat[11] = a03 * sin_y + a23 * cos_y;
}

void
mat4_translate(mat4_t mat, float x, float y, float z)
{
    mat[12] += mat[0] * x + mat[4] * y + mat[8] * z;
    mat[13] += mat[1] * x + mat[5] * y + mat[9] * z;
    mat[14] += mat[2] * x + mat[6] * y + mat[10] * z;
    mat[15] += mat[3] * x + mat[7] * y + mat[11] * z;
}

void
mat4_identity(mat4_t mat)
{
    memcpy(mat, identity, SIZEOF_MAT4);
}
