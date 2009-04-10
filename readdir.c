/*-
 * Copyright (c) 2009 Ed Schouten <ed@80386.nl>
 * All rights reserved.

 * Copyright (c) 2009 Jille Timmermans <jille@quis.cx>
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

struct dirent *
readdir(DIR *d)
{
	static void *func;
	struct dirent *dp;
	unsigned int i;
	int c;

	if (func == NULL) {
		func = dlsym(RTLD_NEXT, SYM("readdir"));
		if (func == NULL)
			abort();
	}
	
	for (;;) {
skip:		dp = ((struct dirent *(*)(DIR *))func)(d);
		if (dp == NULL)
			return (NULL);
		for (i = 0; hide[i] != NULL; i++) {
			c = strcmp(dp->d_name, hide[i]);
			if (c == 0)
				goto skip;
			if (c > 0)
				return (dp);
		}
		return (dp);
	}
}

int
readdir_r(DIR *d, struct dirent *dp, struct dirent **result)
{
	static void *func;
	int ret, c;
	unsigned int i;

	if (func == NULL) {
		func = dlsym(RTLD_NEXT, SYM("readdir_r"));
		if (func == NULL)
			abort();
	}
	
	for (;;) {
skip:		ret = ((int (*)(DIR *, struct dirent *, struct dirent **))func)(d, dp, result);
		if (ret != 0)
			return (ret);
		for (i = 0; hide[i] != NULL; i++) {
			c = strcmp(dp->d_name, hide[i]);
			if (c == 0)
				goto skip;
			if (c > 0)
				return (ret);
		}
		return (ret);
	}
}
