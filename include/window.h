/*
 * Window management.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _WINDOW_H
#define _WINDOW_H

#include <stdbool.h>

void window_shutdown(void);
void window_loop(void);
bool window_init(int width, int height, const char *title);

#endif /* !_WINDOW_H */
