SHLIB_NAME=	libhidesvn.so
SRCS=		hidesvn.c
WARNS?=		6

LIBDIR?=	/usr/local/lib

.include <bsd.lib.mk>
