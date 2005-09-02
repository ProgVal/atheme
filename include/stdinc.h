/*
 * Copyright (c) 2005 William Pitcock et al.
 * Rights to this code are documented in doc/LICENSE.
 *
 * This is the header which includes all of the system stuff.
 *
 * $Id: stdinc.h 1606 2005-08-10 17:40:35Z nenolod $
 */

#ifndef STDINC_H
#define STDINC_H

/* I N C L U D E S */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/stat.h>
#include <ctype.h>
#include <regex.h>

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

/* socket stuff */
#ifndef _WIN32
# include <netdb.h>
# include <netinet/in.h>
# include <unistd.h>
# include <grp.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/socket.h>
# include <fcntl.h>
#else
# include <winsock.h>
# include <windows.h>
# include <sys/timeb.h>
# include <direct.h>
# include <io.h>
# include <fcntl.h>
#endif

#include <sys/types.h>

#include <libgen.h>
#include <dirent.h>

#ifndef _WIN32
typedef enum { ERROR = -1, FALSE, TRUE } l_boolean_t;
#else
typedef int l_boolean_t;
#define FALSE 0
#define TRUE 1
#endif

#undef boolean_t
#define boolean_t l_boolean_t

/* XXX these are all 32-bit types, not that I care. */
#ifdef _WIN32
typedef int int8_t;
typedef int int16_t;
typedef int int24_t;
typedef int int32_t;
typedef long long int64_t;
typedef unsigned int u_int8_t;
typedef unsigned int u_int16_t;
typedef unsigned int u_int24_t;
typedef unsigned int u_int32_t;
typedef unsigned long long u_int64_t;

/* XXX Microsoft headers are broken */
#define snprintf _snprintf
#endif

#endif
