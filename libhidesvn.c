/*-
 * Copyright (c) 2009 Ed Schouten <ed@80386.nl>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

/* Yuck. */
#ifdef __linux__
#define	READDIR_SYM	"readdir64"
#define	READDIR_R_SYM	"readdir_r64"
#define	readdir		readdir64
#define	readdir_r	readdir_r64
#define	dirent		dirent64
#else
#define	READDIR_SYM	"readdir"
#define	READDIR_R_SYM	"readdir_r"
#endif

typedef struct dirent *readdir_t(DIR *);
typedef int readdir_r_t(DIR *, struct dirent *, struct dirent **);

struct dirent *
readdir(DIR *d)
{
	static readdir_t *func;
	struct dirent *dp;

	if (func == NULL) {
		func = (readdir_t *)dlsym(RTLD_NEXT, READDIR_SYM);
		if (func == NULL)
			abort();
	}
	
	do {
		dp = func(d);
	} while (dp != NULL && strcmp(dp->d_name, ".svn") == 0);

	return (dp);
}

int
readdir_r(DIR *d, struct dirent *dp, struct dirent **result)
{
	static readdir_r_t *func;
	int ret;

	if (func == NULL) {
		func = (readdir_r_t *)dlsym(RTLD_NEXT, READDIR_R_SYM);
		if (func == NULL)
			abort();
	}
	
	do {
		ret = func(d, dp, result);
	} while (ret == 0 && strcmp(dp->d_name, ".svn") == 0);

	return (ret);
}
