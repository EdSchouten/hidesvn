all: libhidesvn.so

libhidesvn.so: libhidesvn.c
	$(CC) -o libhidesvn.so -ldl -shared $(CFLAGS) $(LDFLAGS) libhidesvn.c

clean:
	-rm -f libhidesvn.so
