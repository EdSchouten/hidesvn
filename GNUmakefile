all: libhidesvn.so

libhidesvn.so: libhidesvn.c
	$(CC) -o libhidesvn.so -ldl -shared $(CFLAGS) $(LDFLAGS) libhidesvn.c
libhidesvn.dylib: libhidesvn.c
	$(CC) -o libhidesvn.so -ldl -dynamiclib $(CFLAGS) $(LDFLAGS) libhidesvn.c

clean:
	-rm -f libhidesvn.so
