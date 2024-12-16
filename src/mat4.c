/*
 * 4x4 float matrix utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <math.h>
#include <string.h>
#include "mat4.h"

static const float identity[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

void
mat4_perspective(mat4_t mat, float fovy, float aspect, float near, float far)
{
    float f, fn;

    if (mat == NULL) {
        return;
    }

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
    (void)mat;
    (void)x;
    (void)y;
    (void)z;

/*
    TODO: Do this the right way.

    float sin_x, cos_x, sin_y, cos_y, sin_z, cos_z;

    if (mat == NULL) {
        return;
    }

    sin_x = sinf(x);
    cos_x = cosf(x);
    sin_y = sinf(y);
    cos_y = cosf(y);
    sin_z = sinf(z);
    cos_z = cosf(z);

    mat[0] *= cos_y * (cos_z - sin_z);
    mat[1] *= cos_y;
*/
}

void
mat4_translate(mat4_t mat, float x, float y, float z)
{
    if (mat == NULL) {
        return;
    }

    mat[12] += mat[0] * x + mat[4] * y + mat[8] * z;
    mat[13] += mat[1] * x + mat[5] * y + mat[9] * z;
    mat[14] += mat[2] * x + mat[6] * y + mat[10] * z;
    mat[15] += mat[3] * x + mat[7] * y + mat[11] * z;
}

void
mat4_identity(mat4_t mat)
{
    if (mat != NULL) {
        memcpy(mat, identity, SIZEOF_MAT4);
    }
}
