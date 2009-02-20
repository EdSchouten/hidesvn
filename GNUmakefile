all: libhidesvn.so

libhidesvn.so: hidesvn.c
	$(CC) -o libhidesvn.so -ldl -shared $(CFLAGS) $(LDFLAGS) hidesvn.c

clean:
	-rm -f libhidesvn.so
