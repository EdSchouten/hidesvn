all: libhidesvn.so

libhidesvn.so: libhidesvn.c
	$(CC) -o libhidesvn.so -ldl -shared -D_GNU_SOURCE $(CFLAGS) $(LDFLAGS) libhidesvn.c

clean:
	-rm -f libhidesvn.so
