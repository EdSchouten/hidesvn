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
	struct dirent *dp;
	static readdir_t *func;

	if (func == NULL)
		func = (readdir_t *)dlsym(RTLD_NEXT, READDIR_SYM);
	if (func == NULL)
		abort();
	
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

	if (func == NULL)
		func = (readdir_r_t *)dlsym(RTLD_NEXT, READDIR_R_SYM);
	if (func == NULL)
		abort();
	
	do {
		ret = func(d, dp, result);
	} while (ret == 0 && strcmp(dp->d_name, ".svn") == 0);

	return (ret);
}
