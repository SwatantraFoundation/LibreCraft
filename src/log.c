/*
 * Logging utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#include <stdarg.h>
#include <stdio.h>
#include "log.h"

void
__debug(const char *fmt, ...)
{
    va_list args;

    fputs("\033[90m[debug]\033[0m ", stdout);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void
error(const char *fmt, ...)
{
    va_list args;

    fputs("\033[91m[error]\033[0m ", stderr);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}
