all: libhidesvn.so

libhidesvn.so: hidesvn.c
	$(CC) -o libhidesvn.so -ldl -shared -D_GNU_SOURCE $(CFLAGS) $(LDFLAGS) hidesvn.c

clean:
	-rm -f libhidesvn.so
