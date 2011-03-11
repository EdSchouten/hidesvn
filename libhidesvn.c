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

#define	_GNU_SOURCE
#define	_POSIX_C_SOURCE	200809
#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

/*
 * List of names to block. Keep this sorted in reverse order.
 */

static const char *hide[] = { "_darcs", "CVS", ".svn", ".hg", ".git", NULL };

/*
 * Always build replacements for readdir()/readdir_r().
 */

#define	SYM(s)		s
#include "readdir.c"

/*
 * Also build replacements for readdir64()/readdir_r64() for glibc.
 */

#if defined(__GLIBC__) && !defined(BUILT64)
#undef	SYM
#define	SYM(s)		s "64"
#define	readdir		readdir64
#define	readdir_r	readdir_r64
#define	dirent		dirent64
#include "readdir.c"
#endif
