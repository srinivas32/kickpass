/*
 * Copyright (c) 2015 Paul Fariello <paul@fariello.eu>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdarg.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

char *
kp_log_decorate(kp_error_t err, const char *fmt)
{
	char *_fmt;

	if (asprintf(&_fmt, "%s: %s", fmt, kp_strerror(err)) < 0) {
		errx(ENOMEM, "memory error");
	}

	return _fmt;
}

__attribute__((format(printf, 2, 3)))
void
kp_err(kp_error_t err, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (err == KP_ERRNO) {
		verr(err, fmt, ap);
	} else {
		char *_fmt;
		_fmt = kp_log_decorate(err, fmt);
		verrx(err, _fmt, ap);
		free(_fmt);
	}
	va_end(ap);
}

__attribute__((format(printf, 2, 3)))
void
kp_warn(kp_error_t err, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	if (err == KP_ERRNO) {
		vwarn(fmt, ap);
	} else {
		char *_fmt;
		_fmt = kp_log_decorate(err, fmt);
		vwarnx(_fmt, ap);
		free(_fmt);
	}
	va_end(ap);
}

__attribute__((format(printf, 2, 3)))
void
kp_errx(kp_error_t err, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	verrx(err, fmt, ap);
	va_end(ap);
}

__attribute__((format(printf, 2, 3)))
void
kp_warnx(kp_error_t err, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vwarnx(fmt, ap);
	va_end(ap);
}
