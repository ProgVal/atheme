/*
 * $Id$
 *
 * Copyright Metaparadigm Pte. Ltd. 2004.
 * Michael Clark <michael@metaparadigm.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public (LGPL)
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details: http://www.gnu.org/
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/param.h>

#include "json/debug.h"


static int _syslog = 0;
static int _debug = 0;

void mc_set_debug(int debug)
{
	_debug = debug;
}

int mc_get_debug()
{
	return _debug;
}

extern void mc_set_syslog(int syslog)
{
	_syslog = syslog;
}

void mc_abort(const char *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	vprintf(msg, ap);
	exit(1);
}

void mc_debug(const char *msg, ...)
{
	va_list ap;
	if (_debug)
	{
		va_start(ap, msg);
		vprintf(msg, ap);
	}
}

void mc_error(const char *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	vfprintf(stderr, msg, ap);
}

void mc_info(const char *msg, ...)
{
	va_list ap;
	va_start(ap, msg);
	vfprintf(stderr, msg, ap);
}

/* vim:cinoptions=>s,e0,n0,f0,{0,}0,^0,=s,ps,t0,c3,+s,(2s,us,)20,*30,gs,hs ts=8 sw=8 noexpandtab
*/
