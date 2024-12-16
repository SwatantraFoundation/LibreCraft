/*
 * Logging utilities.
 * Copyright (c) 2024, the Swatantra Foundation.
 * Provided under the BSD 3-Clause license.
 */

#ifndef _LOG_H
#define _LOG_H

void __debug(const char *fmt, ...);
void error(const char *fmt, ...);

#ifdef ENABLE_DEBUG
#define debug __debug
#else
#define debug(fmt, ...)
#endif

#endif /* !_LOG_H */
